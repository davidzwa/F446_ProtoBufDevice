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
#include "device_messages.h"
#include "measurements.h"
#include "radio_config.h"
#include "radio_phy.h"
#include "uart.h"
#include "tasks.h"
#include "uart_messages.h"
#include "utilities.h"
#include "utils.h"

#define PROTO_LIMITS MAX_APPNAME_LENGTH, MAX_PAYLOAD_LENGTH, MAX_PAYLOAD_LENGTH
#define PACKET_SIZE_LIMIT 256
uint8_t encodedBuffer[PACKET_SIZE_LIMIT];
uint8_t packetBufferingLength = 0;
uint8_t packetSize;
uint16_t actualSize;
uint8_t packetEndMarker = '\0';
bool pendingConfigChange = false;
const size_t offset = 1;  // End byte

ProtoReadBuffer readBuffer;
ProtoWriteBuffer writeBuffer;
bool newCommandReceived = false;
RadioRxConfig rxConf;
RadioTxConfig txConf;
UartCommand<MAX_PAYLOAD_LENGTH> uartCommand;

extern Uart_t Uart2;
Uart_t *uart = &Uart2;
void UartISR(UartNotifyId_t id);
void UartSend(uint8_t *buffer, size_t length);

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

void UartSend(uint8_t *buffer, size_t length) {
    uint8_t encodedBuffer[length * 2];
    size_t encodedSize = COBS::encode(buffer, length, encodedBuffer);
    UartPutChar(uart, 0xFF);
    UartPutChar(uart, encodedSize);
    UartPutBuffer(uart, encodedBuffer, encodedSize);
    UartPutChar(uart, 0x0);
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

    if (packetBufferingLength == 0 && GetLastChar(0) == 0xFF) {
        FifoPop(&uart->FifoRx);
        packetBufferingLength++;
        return;
    }

    if (packetBufferingLength == 1) {
        packetSize = FifoPop(&uart->FifoRx);
    }
    packetBufferingLength++;

    // This is a very weak check
    if (GetFifoRxLength() >= packetSize + 1 || GetLastChar(0) == packetEndMarker) {
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
        printf("ID %ld\n", (uint32_t)uartCommand.get_which_Body());
        rxConf = uartCommand.get_rxConfig();
        UartSendAck(1);
        // TODO apply
    } else if (uartCommand.has_txConfig()) {
        printf("ID %ld\n\0", (uint32_t)uartCommand.get_which_Body());
        txConf = uartCommand.get_txConfig();
        UartSendAck(1);
        // TODO apply
    } else if (uartCommand.has_transmitCommand()) {
        TransmitCommand<MAX_PAYLOAD_LENGTH> command = uartCommand.get_transmitCommand();
        if (command.has_Period() && command.get_Period() > 50) {
            TogglePeriodicTx(command.get_Period(), command.get_MaxPacketCount());
        } else {
            TransmitUnicast(command);
        }

        UartSendAck(1);
    } else if (uartCommand.has_requestBootInfo()) {
        UartSendBoot();
    } else if (uartCommand.has_clearMeasurementsCommand()) {
        ClearMeasurements();

        if (uartCommand.get_clearMeasurementsCommand().get_SendBootAfter()) {
            UartSendBoot();
        }
        else {
            UartSendAck(1);
        }
    } else if (uartCommand.has_deviceConfiguration()) {
        auto config = uartCommand.get_deviceConfiguration();
        bool alwaysSend = config.get_EnableAlwaysSend();
        auto alwaysSendPeriod = config.get_AlwaysSendPeriod();
        ApplyAlwaysSendPeriodically(alwaysSend, alwaysSendPeriod);
        UartSendAck(1);
    } else {
        UartSendAck(250);
    }

    uartCommand.clear();
}

void UartResponseSend(UartResponse<PROTO_LIMITS> & response) {
    // First the length
    writeBuffer.push((uint8_t)response.serialized_size());
    // Push the data
    auto result = response.serialize(writeBuffer);
    if (result == ::EmbeddedProto::Error::NO_ERRORS) {
        // Send the buffer in COBS encoded form
        writeBuffer.push(packetEndMarker);
        UartSend(writeBuffer.get_data(), writeBuffer.get_size());
    }
    writeBuffer.clear();
}

void UartSendAck(uint8_t code) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& ack = uartResponse.mutable_ackMessage();
    ack.set_Code(code);

    UartResponseSend(uartResponse);
}

void UartDebug(const char* payload, uint32_t code, size_t length) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& debugMessage = uartResponse.mutable_debugMessage();
    debugMessage.set_Code(code);
    auto& debugPayload = debugMessage.mutable_Payload();
    debugPayload.set((uint8_t*)payload, length);

    UartResponseSend(uartResponse);
}

void UartSendLoRaRxError() {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& loraMessage = uartResponse.mutable_loraMeasurement();
    loraMessage.set_Success(false);
    
    UartResponseSend(uartResponse);
}

void UartSendLoRaRx(const EmbeddedProto::FieldBytes<MAX_PAYLOAD_LENGTH> payload, uint32_t sequenceNumber, int16_t rssi, int8_t snr, bool isMeasurementFragment) {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& loraMessage = uartResponse.mutable_loraMeasurement();
    loraMessage.set_Rssi(rssi);
    loraMessage.set_IsMeasurementFragment(isMeasurementFragment);
    loraMessage.set_Success(true);
    loraMessage.set_Snr(snr);
    loraMessage.set_SequenceNumber(sequenceNumber);
    loraMessage.set_Payload(payload);

    UartResponseSend(uartResponse);
}

void UartSendBoot() {
    UartResponse<PROTO_LIMITS> uartResponse;
    auto& bootMessage = uartResponse.mutable_bootMessage();
    bootMessage.mutable_AppName() = APP_NAME;
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

    Radio.Rx(RX_TIMEOUT_VALUE);
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
