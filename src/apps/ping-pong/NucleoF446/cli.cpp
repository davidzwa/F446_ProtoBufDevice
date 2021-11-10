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
#include "radio_config.h"
#include "tx.h"
#include "uart.h"
#include "uart_messages.h"
#include "utilities.h"
#include "utils.h"

#define PACKET_SIZE_LIMIT 256
#define MAX_PAYLOAD_LENGTH 22
#define MAX_APPNAME_LENGTH 20
uint8_t encodedBuffer[PACKET_SIZE_LIMIT];
uint16_t actualSize;
uint8_t packetEndMarker = '\0';
bool pendingConfigChange = false;
const size_t offset = 1;

ProtoReadBuffer readBuffer;
ProtoWriteBuffer writeBuffer;
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

uint8_t GetLastChar() {
    return uart->FifoRx.Data[uart->FifoRx.End];
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

    if (GetLastChar() == packetEndMarker) {
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
            if (uartCommand.has_RxConfig()) {
                printf("RX%ld\n", (uint32_t)uartCommand.get_which_Body());
                txConf = uartCommand.get_TxConfig();
                // TODO apply
            }
            if (uartCommand.has_TxConfig()) {
                printf("TX%ld\n", (uint32_t)uartCommand.get_which_Body());
                rxConf = uartCommand.get_RxConfig();
                // TODO apply
            }
            if (uartCommand.has_transmitCommand()) {
                TransmitCommand<MAX_PAYLOAD_LENGTH> command = uartCommand.get_transmitCommand();
                printf("ID %ld %d\n", (uint32_t)command.get_DeviceId(), (bool)command.get_IsMulticast());
                // TODO apply
            }
            if (uartCommand.has_requestBootInfo()) {
                UartSendBoot();
            }
        }
    }
}

void UartSend(uint8_t *buffer, size_t length) {
    uint8_t encodedBuffer[length * 2];
    size_t encodedSize = COBS::encode(buffer, length, encodedBuffer);
    UartPutBuffer(uart, encodedBuffer, encodedSize);
}

void UartSendBoot() {
    UartResponse<MAX_APPNAME_LENGTH> uartResponse;
    auto bootMessage = uartResponse.mutable_bootMessage();
    bootMessage.mutable_AppName() = APP_NAME;
    bootMessage.mutable_DeviceIdentifier() = GetDeviceId();
    const Version_t appVersion = {.Value = FIRMWARE_VERSION};
    bootMessage.mutable_FirmwareVersion().set_Major(appVersion.Fields.Major);
    bootMessage.mutable_FirmwareVersion().set_Minor(appVersion.Fields.Minor);
    bootMessage.mutable_FirmwareVersion().set_Patch(appVersion.Fields.Patch);
    bootMessage.mutable_FirmwareVersion().set_Revision(appVersion.Fields.Revision);
    uartResponse.set_bootMessage(bootMessage);

    writeBuffer.clear();
    // First the length
    writeBuffer.push((uint8_t)uartResponse.serialized_size());
    // Push the data
    auto result = uartResponse.serialize(writeBuffer);
    if (result == ::EmbeddedProto::Error::NO_ERRORS) {
        // Send the buffer in COBS encoded form
        writeBuffer.push(packetEndMarker);
        UartSend(writeBuffer.get_data(), writeBuffer.get_size());
    }
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

void UpdateRadioSpreadingFactor(uint8_t spreadingFactor, bool reconnect) {
    txConf.set_DataRate(spreadingFactor);
    rxConf.set_DataRate(spreadingFactor);

    if (reconnect) {
        ApplyRadioConfig();
    }
}

void ProcessSpreadingFactorMessage(uint8_t spreadingFactor, bool broadcastLoRa) {
    if (IsValidSpreadingFactor(spreadingFactor)) {
        if (broadcastLoRa) {
            TxSpreadingFactor(spreadingFactor);
            printf("[CLI] Broadcasting SF %d\n\r", spreadingFactor);

            pendingConfigChange = true;
            UpdateRadioSpreadingFactor(spreadingFactor, false);
        } else {
            UpdateRadioSpreadingFactor(spreadingFactor, true);
        }

        printf("[CLI] Set Radio SF '%d' \n\r", spreadingFactor);
    } else {
        printf("[CLI] SF not 7,8,9,0,1,2(=12) skipped: '%c'\n\r", spreadingFactor);
    }
}

void ApplyConfigIfPending() {
    if (!pendingConfigChange)
        return;
    pendingConfigChange = false;
    ApplyRadioConfig();
}
