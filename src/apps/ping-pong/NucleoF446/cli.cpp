#include "cli.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "COBS.h"
#include "Crc8.h"
#include "ProtoReadBuffer.h"
#include "ProtoWriteBuffer.h"
#include "config.h"
#include "delay.h"
#include "measurements.h"
#include "nvm_rlnc.h"
#include "radio_config.h"
#include "radio_phy.h"
#include "tasks.h"
#include "uart.h"
#include "uart_control_messages.h"
#include "uart_device_messages.h"
#include "utilities.h"
#include "utils.h"

#define PKT_START 0xFF
#define PKT_END 0x00
#define PACKET_SIZE_LIMIT 256
#define PROTO_LIMITS PACKET_SIZE_LIMIT, MAX_LORA_BYTES

uint8_t encodedBuffer[PACKET_SIZE_LIMIT];
uint8_t packetBufferingLength = 0;
uint8_t packetSize;
uint16_t actualSize;
bool pendingConfigChange = false;
#define OFFSET_OUTER 1  // End byte
#define OFFSET_INNER 2  // Length and crc byte

ProtoReadBuffer readBuffer;
ProtoWriteBuffer writeBuffer;
bool newCommandReceived = false;
bool checksumSuccess = false;
UartCommand<MAX_LORA_BYTES> uartCommand;

extern Uart_t Uart2;
Uart_t* uart = &Uart2;
void UartISR(UartNotifyId_t id);
void UartSend(uint8_t* buffer, size_t length);

void InitCli(bool withISR = true) {
    if (withISR) {
        Uart2.IrqNotify = UartISR;
    }
}

uint16_t GetFifoRxLength() {
    return uart->FifoRx.End - uart->FifoRx.Begin;
}

uint8_t GetLastChar(uint8_t offset) {
    return uart->FifoRx.Data[uart->FifoRx.End - offset];
}

void UartSend(uint8_t* buffer, size_t length) {
    uint8_t encodedBuffer[length * 2];
    size_t encodedSize = COBS::encode(buffer, length, encodedBuffer);
    UartPutChar(uart, PKT_START);
    UartPutChar(uart, encodedSize);
    UartPutBuffer(uart, encodedBuffer, encodedSize);
    UartPutChar(uart, PKT_END);
}

void UartISR(UartNotifyId_t id) {
    if (id == UART_NOTIFY_TX) {
        return;
    }

    if (IsFifoEmpty(&uart->FifoRx)) {
        // Illegal scenario
        return;
    }

    if (GetFifoRxLength() > PACKET_SIZE_LIMIT) {
        // Erroneous scenario
        FifoFlush(&uart->FifoRx);
    }

    if (packetBufferingLength == 0 && GetLastChar(0) == PKT_START) {
        FifoPop(&uart->FifoRx);
        packetBufferingLength++;
        return;
    }

    if (packetBufferingLength == 1) {
        packetSize = FifoPop(&uart->FifoRx);
    }
    packetBufferingLength++;

    // This is a very weak check
    if (GetFifoRxLength() >= packetSize + 1 || GetLastChar(0) == PKT_END) {
        bool result = UartGetBuffer(uart, encodedBuffer, PACKET_SIZE_LIMIT, &actualSize);
        if (result == 1) {
            return;  // Error occurred
        }

        // Remove length and type bytes
        uint8_t packetSize = actualSize - OFFSET_OUTER;
        uint8_t decodedBuffer[actualSize];

        // Decode 0x00
        COBS::decode(encodedBuffer, packetSize, decodedBuffer);

        // Store crc and length bytes
        uint8_t crc8 = decodedBuffer[0];
        size_t n_bytes = decodedBuffer[1];

        // Store packet for deserialization
        for (size_t i = OFFSET_INNER; i < (n_bytes + OFFSET_INNER); i++) {
            readBuffer.push(decodedBuffer[i]);
        }

        auto checksumResult = ComputeChecksum(readBuffer.get_data_array(), readBuffer.get_size());
        checksumSuccess = crc8 == checksumResult;
        if (!checksumSuccess) {
            // Process CRC failure
            UartDebug("CRC_FAIL_UART", 400, 14);
            UartDebug((const char*)readBuffer.get_data_array(), (uint32_t)checksumResult, readBuffer.get_size());
        } else {
            auto deserialize_status = uartCommand.deserialize(readBuffer);
            if (::EmbeddedProto::Error::NO_ERRORS == deserialize_status) {
                // Let main loop pick it up
                newCommandReceived = true;
            } else {
                UartDebug("PROTO_FAIL", (uint32_t)deserialize_status, 10);
            }
        }

        readBuffer.clear();
        packetSize = 0;
        packetBufferingLength = 0;
    }
}

void ResetCrcFailure() {
    newCommandReceived = false;
}

bool IsCrcValid() {
    return checksumSuccess;
}

bool IsCliCommandReady() {
    return newCommandReceived;
}

void ProcessCliCommand() {
    if (newCommandReceived == false) {
        return;
    }

    // We dont want to process twice, so we immediately set it to false
    newCommandReceived = false;

    if (uartCommand.has_txConfig()) {
        auto txConf = uartCommand.get_txConfig();
        SetTxPower(txConf.get_Power());
        UartSendAck(txConf.get_Power());
        // TODO apply
    } else if (uartCommand.has_transmitCommand()) {
        LORA_MSG_TEMPLATE command = uartCommand.get_transmitCommand();
        auto targetDeviceId = command.get_DeviceId();

        if (IsDeviceId(targetDeviceId) || uartCommand.get_DoNotProxyCommand()) {
            // Immediately dump the payload 'as if LoRa received it' including unicast/multicast setting
            HandleLoRaProtoPayload(command, -1, -1);
        } else {
            TransmitLoRaMessage(command);
            UartSendAck(1);
        }
    } else if (uartCommand.has_requestBootInfo()) {
        UartSendBoot();
    } else if (uartCommand.has_clearMeasurementsCommand()) {
        ClearMeasurements();

        if (uartCommand.get_clearMeasurementsCommand().get_SendBootAfter()) {
            UartSendBoot();
        } else {
            UartSendAck(1);
        }
    } else if (uartCommand.has_deviceConfiguration()) {
        // Set the Radio configuration or sequence config
        auto config = uartCommand.get_deviceConfiguration();
        
        if (config.get_applyTransmitConfig()) {
            SetTxRxConfig(config.get_transmitConfiguration(), true);
        }

        if (config.get_enableSequenceTransmit()) {
            ApplyAlwaysSendPeriodically(config);
        }
        else {
            StopPeriodicTransmit();
        }

        UartSendAck(1);
    } else {
        UartSendAck(250);
    }

    uartCommand.clear();
}

void UartResponseSend(UartResponse<PROTO_LIMITS>& response) {
    // First the length
    writeBuffer.push((uint8_t)response.serialized_size());
    // Push the data
    auto result = response.serialize(writeBuffer);
    if (result == ::EmbeddedProto::Error::NO_ERRORS) {
        UartSend(writeBuffer.get_data(), writeBuffer.get_size());
    } else {
        UartDebug("PROTO_FAIL_TX", 404, 10);
    }
    writeBuffer.clear();
}

void UartSendAck(uint8_t code) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& ack = uartResponse.mutable_ackMessage();
    ack.set_Code(code);

    UartResponseSend(uartResponse);
}

void UartSendDecodingUpdateWithoutPayload(DecodingUpdate& update) {
    UartResponse<PROTO_LIMITS> uartResponse;
    uartResponse.set_decodingUpdate(update);
    UartResponseSend(uartResponse);
}

void UartSendDecodingUpdate(DecodingUpdate& update, uint8_t* debugPayload, size_t length) {
    UartResponse<PROTO_LIMITS> uartResponse;
    uartResponse.set_decodingUpdate(update);
    auto& payload = uartResponse.mutable_Payload();
    payload.set(debugPayload, length);
    UartResponseSend(uartResponse);
}

void UartSendDecodingMatrix(DecodingMatrix& sizes, uint8_t* matrix, size_t length) {
    UartResponse<PROTO_LIMITS> uartResponse;
    uartResponse.set_decodingMatrix(sizes);
    auto& payload = uartResponse.mutable_Payload();
    payload.set(matrix, length);
    UartResponseSend(uartResponse);
}

void UartSendDecodingResult(DecodingResult& result) {
    UartResponse<PROTO_LIMITS> uartResponse;
    uartResponse.set_decodingResult(result);
    UartResponseSend(uartResponse);
}

void UartThrow(const char* payload, size_t length) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& exceptionPayload = uartResponse.mutable_Payload();
    exceptionPayload.set((uint8_t*)payload, length);

    UartResponseSend(uartResponse);
}

void UartDebug(const char* payload, uint32_t code, size_t length) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& debugMessage = uartResponse.mutable_debugMessage();
    debugMessage.set_Code(code);
    auto& debugPayload = uartResponse.mutable_Payload();
    debugPayload.set((uint8_t*)payload, length);

    UartResponseSend(uartResponse);
}

void UartSendLoRaRxError() {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& loraMessage = uartResponse.mutable_loraMeasurement();
    loraMessage.set_Success(false);

    UartResponseSend(uartResponse);
}

void UartSendLoRaRx(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr, bool isMeasurementFragment) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& loraMeasurement = uartResponse.mutable_loraMeasurement();
    loraMeasurement.set_Rssi(rssi);
    loraMeasurement.set_IsMeasurementFragment(isMeasurementFragment);
    loraMeasurement.set_Success(true);
    loraMeasurement.set_Snr(snr);
    loraMeasurement.set_SequenceNumber(message.get_CorrelationCode());
    loraMeasurement.set_DownlinkPayload(message);

    UartResponseSend(uartResponse);
}

void UartSendBoot() {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& bootMessage = uartResponse.mutable_bootMessage();
    uartResponse.mutable_Payload().set((uint8_t*)APP_NAME, 13);
    bootMessage.mutable_DeviceIdentifier() = GetDeviceId();
    bootMessage.set_MeasurementCount(GetMeasurementCount());
    bootMessage.set_MeasurementsDisabled(IsStorageDirtyAndLocked());
    bootMessage.set_RlncFlashState(GetRlncFlashState());
    bootMessage.set_RlncSessionState(GetRlncSessionState());
    auto& version = bootMessage.mutable_FirmwareVersion();
    const Version_t appVersion = {.Value = FIRMWARE_VERSION};
    version.set_Major(appVersion.Fields.Major);
    version.set_Minor(appVersion.Fields.Minor);
    version.set_Patch(appVersion.Fields.Patch);
    version.set_Revision(appVersion.Fields.Revision);

    UartResponseSend(uartResponse);
}
