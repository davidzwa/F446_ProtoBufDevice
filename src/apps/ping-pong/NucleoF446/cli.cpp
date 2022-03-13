#include "cli.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "COBS.h"
#include "ProtoReadBuffer.h"
#include "ProtoWriteBuffer.h"
#include "config.h"
#include "delay.h"
#include "measurements.h"
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
#define PROTO_LIMITS MAX_LORA_BYTES, MAX_LORA_BYTES
#define PACKET_SIZE_LIMIT 256

uint8_t encodedBuffer[PACKET_SIZE_LIMIT];
uint8_t packetBufferingLength = 0;
uint8_t packetSize;
uint16_t actualSize;
bool pendingConfigChange = false;
const size_t offset = 1;  // End byte

ProtoReadBuffer readBuffer;
ProtoWriteBuffer writeBuffer;
bool newCommandReceived = false;
RadioRxConfig rxConf;
RadioTxConfig txConf;
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
        uint8_t packetSize = actualSize - offset;
        uint8_t decodedBuffer[actualSize];

        // Decode and store
        COBS::decode(encodedBuffer, packetSize, decodedBuffer);
        uint8_t n_bytes = decodedBuffer[0];
        for (size_t i = offset; i <= n_bytes; i++) {
            readBuffer.push(decodedBuffer[i]);
        }

        auto deserialize_status = uartCommand.deserialize(readBuffer);
        if (::EmbeddedProto::Error::NO_ERRORS == deserialize_status) {
            // Let main loop pick it up
            newCommandReceived = true;
        }

        readBuffer.clear();
        packetSize = 0;
        packetBufferingLength = 0;
    }
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

    if (uartCommand.has_rxConfig()) {
        rxConf = uartCommand.get_rxConfig();
        UartSendAck(1);
        // TODO apply
    } else if (uartCommand.has_txConfig()) {
        txConf = uartCommand.get_txConfig();
        SetTxPower(txConf.get_Power());
        UartSendAck(txConf.get_Power());
        // TODO apply
    } else if (uartCommand.has_transmitCommand()) {
        // TODO verify if within SF/ToA limits?
        LORA_MSG_TEMPLATE command = uartCommand.get_transmitCommand();
        auto targetDeviceId = command.get_DeviceId();

        // Immediately dump the payload 'as if LoRa received it'
        if (IsDeviceId(targetDeviceId) || uartCommand.get_doNotProxyCommand()) {
            HandleLoRaProtoPayload(command, -1, -1);
        } else {
            TransmitLoRaMessage(command);
            UartSendAck(1);
        }
    } else if (uartCommand.has_requestBootInfo()) {
        UartSendBoot();
    } else if (uartCommand.has_resetRadio()) {
        // Clears the radio chip and transmit queue
        InitRadioPhy();
    } else if (uartCommand.has_clearMeasurementsCommand()) {
        ClearMeasurements();

        if (uartCommand.get_clearMeasurementsCommand().get_SendBootAfter()) {
            UartSendBoot();
        } else {
            UartSendAck(1);
        }
    } else if (uartCommand.has_deviceConfiguration()) {
        auto config = uartCommand.get_deviceConfiguration();
        bool alwaysSend = config.get_EnableAlwaysSend();
        auto alwaysSendPeriod = config.get_AlwaysSendPeriod();
        auto limitedPacketCount = config.get_LimitedSendCount();
        ApplyAlwaysSendPeriodically(alwaysSend, alwaysSendPeriod, limitedPacketCount);
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
    }
    else {
        // UartDebug("PROTO")
    }
    writeBuffer.clear();
}

void UartSendAck(uint8_t code) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& ack = uartResponse.mutable_ackMessage();
    ack.set_Code(code);

    UartResponseSend(uartResponse);
}

void UartSendDecodingResult(bool success, uint8_t matrixRank, uint8_t firstDecodedNumber, uint8_t lastDecodedNumber) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& decodingResult = uartResponse.mutable_decodingResult();
    decodingResult.set_Success(success);
    decodingResult.set_MatrixRank(matrixRank);
    decodingResult.set_FirstDecodedNumber(firstDecodedNumber);
    decodingResult.set_LastDecodedNumber(lastDecodedNumber);

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
    // Problematic (sizeof not working, or last char not accepted)
    uartResponse.mutable_Payload().set((uint8_t*)APP_NAME, 13);
    bootMessage.mutable_DeviceIdentifier() = GetDeviceId();
    bootMessage.set_MeasurementCount(GetMeasurementCount());
    bootMessage.set_MeasurementsDisabled(IsStorageDirtyAndLocked());
    auto& version = bootMessage.mutable_FirmwareVersion();
    const Version_t appVersion = {.Value = FIRMWARE_VERSION};
    version.set_Major(appVersion.Fields.Major);
    version.set_Minor(appVersion.Fields.Minor);
    version.set_Patch(appVersion.Fields.Patch);
    version.set_Revision(appVersion.Fields.Revision);

    UartResponseSend(uartResponse);
}

void InitRadioTxConfigLoRa() {
    txConf.set_Modem(RadioModems::MODEM_LORA);
    txConf.set_Power(TX_OUTPUT_POWER);
    txConf.set_Fdev(0);
    txConf.set_Bandwidth(LORA_BANDWIDTH);
    txConf.set_DataRate(LORA_SPREADING_FACTOR);
    txConf.set_CodeRate(LORA_CODINGRATE);
    txConf.set_PreambleLen(LORA_PREAMBLE_LENGTH);
    txConf.set_FixLen(LORA_FIX_LENGTH_PAYLOAD_ON);
    txConf.set_CrcOn(false);
    txConf.set_FreqHopOn(0);
    txConf.set_HopPeriod(0);
    txConf.set_IqInverted(LORA_IQ_INVERSION_ON);
    txConf.set_Timeout(RX_TIMEOUT_VALUE);
}

void InitRadioRxConfigLoRa() {
    rxConf.set_Modem(RadioModems::MODEM_LORA);
    rxConf.set_Bandwidth(LORA_BANDWIDTH);
    rxConf.set_DataRate(LORA_SPREADING_FACTOR);
    rxConf.set_CodeRate(LORA_CODINGRATE);
    rxConf.set_BandwidthAfc(0);
    rxConf.set_PreambleLen(LORA_PREAMBLE_LENGTH);
    rxConf.set_FixLen(LORA_FIX_LENGTH_PAYLOAD_ON);
    rxConf.set_PayloadLen(0);
    rxConf.set_CrcOn(false);
    rxConf.set_FreqHopOn(0);
    rxConf.set_HopPeriod(0);
    rxConf.set_IqInverted(LORA_IQ_INVERSION_ON);
    rxConf.set_RxContinuous(true);
}

void InitRadioConfig() {
    InitRadioTxConfigLoRa();
    InitRadioRxConfigLoRa();
}

void ApplyRadioTxConfig() {
    Radio.SetTxConfig(
        (RadioModems_t)txConf.Modem(), txConf.Power(), txConf.Fdev(), txConf.Bandwidth(),
        txConf.DataRate(), txConf.CodeRate(),
        txConf.PreambleLen(), txConf.FixLen(),
        txConf.CrcOn(), txConf.FreqHopOn(), txConf.HopPeriod(), txConf.IqInverted(), txConf.Timeout());

    Radio.SetChannel(RF_FREQUENCY);
}

void ApplyRadioRxConfig() {
    Radio.SetRxConfig(
        (RadioModems_t)rxConf.Modem(), rxConf.Bandwidth(),
        rxConf.DataRate(), rxConf.CodeRate(),
        rxConf.BandwidthAfc(), rxConf.PreambleLen(),
        rxConf.SymbTimeout(), rxConf.FixLen(), rxConf.PayloadLen(),
        rxConf.CrcOn(), rxConf.FreqHopOn(), rxConf.HopPeriod(), rxConf.IqInverted(), rxConf.RxContinuous());
}

void ApplyRadioConfig() {
    ApplyRadioTxConfig();
    ApplyRadioRxConfig();

    Radio.Rx(0);
}

void SetTxPower(int8_t power) {
    txConf.set_Power(power);

    ApplyRadioTxConfig();
}

void PrintSettings() {
    printf("--RADIO SETTINGS--\nModem:%d\n\tPower:%ld\n\tFdev:%lu\n\tBandwidth:%lu\n\tDataRate:%lu\n\tCodeRate:%lu\n\tPreambleLen:%lu\n\tFixLen:%d\n\tCrCOn:%d\n\tFreqHopOn:%d\n\tHopPeriod:%lu\n\tIqInverted:%d\n\tTimeout:%lu\n--END OF RADIO SETTINGS--\n",
           (int)txConf.Modem(), txConf.Power(), txConf.Fdev(), txConf.Bandwidth(), txConf.DataRate(), txConf.CodeRate(), txConf.PreambleLen(),
           txConf.FixLen(), txConf.CrcOn(), txConf.FreqHopOn(), txConf.HopPeriod(), txConf.IqInverted(), txConf.Timeout());

    // TODO RX settings
    // , % ld, % ld, % d, % ld, % d, % d, % d, % d, % d, % d, % d, % d
    // printf("", rxConfig.Modem, rxConfig.Bandwidth, rxConfig.DataRate, rxConfig.CodeRate, rxConfig.BandwidthAfc, rxConfig.PreambleLen, rxConfig.FixLen, rxConfig.PayloadLen, rxConfig.CrcOn, rxConfig.FreqHopOn, rxConfig.HopPeriod, rxConfig.IqInverted, rxConfig.RxContinuous);
}

void UpdateRadioSpreadingFactor(uint8_t spreadingFactorRx, uint8_t spreadingFactorTx, bool reconnect) {
    txConf.set_DataRate(spreadingFactorTx);
    rxConf.set_DataRate(spreadingFactorRx);

    if (reconnect) {
        ApplyRadioConfig();
    }
}

void ApplyConfigIfPending() {
    if (!pendingConfigChange)
        return;
    pendingConfigChange = false;
    ApplyRadioConfig();
}
