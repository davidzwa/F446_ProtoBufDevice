#include "cli.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "COBS.h"
#include "UartReadBuffer.h"
#include "delay.h"
#include "radio_config.h"
#include "uart_messages.h"
#include "tx.h"
#include "uart.h"
#include "utils.h"

#define PACKET_SIZE_LIMIT 256
uint8_t encodedBuffer[PACKET_SIZE_LIMIT];
uint16_t actualSize;
uint8_t packetEndMarker = '\0';
bool pendingConfigChange = false;

UartReadBuffer read_buffer;
Command received_command;

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

        uint8_t packetSize = actualSize - 1;
        uint8_t decodedBuffer[actualSize];
        size_t newSize = COBS::decode(encodedBuffer, packetSize, decodedBuffer);

        uint8_t n_bytes = decodedBuffer[0];
        for (size_t i = 1; i <= n_bytes; i++) {
            read_buffer.push(decodedBuffer[i]);
        }

        auto deserialize_status = received_command.deserialize(read_buffer);
        if (::EmbeddedProto::Error::NO_ERRORS == deserialize_status) {
            auto value = received_command.get_value();
            auto button = received_command.get_button();
            UartSend(decodedBuffer, newSize);
        }
    }
}

void UartSend(uint8_t *buffer, size_t length) {
    uint8_t encodedBuffer[length * 2];
    size_t encodedSize = COBS::encode(buffer, length, encodedBuffer);
    UartPutBuffer(uart, encodedBuffer, encodedSize);
}

#if defined(USE_MODEM_LORA)
RadioTXConfig_t txConfig = {
    .Modem = MODEM_LORA,
    .Power = TX_OUTPUT_POWER,
    .Fdev = 0,
    .Bandwidth = LORA_BANDWIDTH,
    .DataRate = LORA_SPREADING_FACTOR,
    .CodeRate = LORA_CODINGRATE,
    .PreambleLen = LORA_PREAMBLE_LENGTH,
    .FixLen = LORA_FIX_LENGTH_PAYLOAD_ON,
    .CrcOn = false,  // true,
    .FreqHopOn = 0,
    .HopPeriod = 0,
    .IqInverted = LORA_IQ_INVERSION_ON,
    .Timeout = true};

RadioRXConfig_t rxConfig = {
    .Modem = MODEM_LORA,
    .Bandwidth = LORA_BANDWIDTH,
    .DataRate = LORA_SPREADING_FACTOR,
    .CodeRate = LORA_CODINGRATE,
    .BandwidthAfc = 0,
    .PreambleLen = LORA_PREAMBLE_LENGTH,
    .FixLen = LORA_FIX_LENGTH_PAYLOAD_ON,
    .PayloadLen = 0,
    .CrcOn = false,  // true,
    .FreqHopOn = 0,
    .HopPeriod = 0,
    .IqInverted = LORA_IQ_INVERSION_ON,
    .RxContinuous = true};
#else
#error "FSK is not yet working"
#endif

void InitRadioTXConfigLoRaDefault(RadioTXConfig_t *txConfig_p) {
    txConfig_p->Modem = MODEM_LORA;
    txConfig_p->Power = TX_OUTPUT_POWER;
    txConfig_p->Fdev = 0;
    txConfig_p->Bandwidth = LORA_BANDWIDTH;
    txConfig_p->DataRate = LORA_SPREADING_FACTOR;
    txConfig_p->CodeRate = LORA_CODINGRATE;
    txConfig_p->PreambleLen = LORA_PREAMBLE_LENGTH;
    txConfig_p->FixLen = LORA_FIX_LENGTH_PAYLOAD_ON;
    txConfig_p->CrcOn = false,  // true;
        txConfig_p->FreqHopOn = 0;
    txConfig_p->HopPeriod = 0;
    txConfig_p->IqInverted = LORA_IQ_INVERSION_ON;
    txConfig_p->Timeout = true;
}

void InitRadioRXConfigLoRaDefault(RadioRXConfig_t *rxConfig_p) {
    rxConfig_p->Modem = MODEM_LORA;
    rxConfig_p->Bandwidth = LORA_BANDWIDTH;
    rxConfig_p->DataRate = LORA_SPREADING_FACTOR;
    rxConfig_p->CodeRate = LORA_CODINGRATE;
    rxConfig_p->BandwidthAfc = 0;
    rxConfig_p->PreambleLen = LORA_PREAMBLE_LENGTH;
    rxConfig_p->FixLen = LORA_FIX_LENGTH_PAYLOAD_ON;
    rxConfig_p->PayloadLen = 0;
    rxConfig_p->CrcOn = false,  // true;
        rxConfig_p->FreqHopOn = 0;
    rxConfig_p->HopPeriod = 0;
    rxConfig_p->IqInverted = LORA_IQ_INVERSION_ON;
    rxConfig_p->RxContinuous = true;
}

void ApplyRadioTXConfig() {
    Radio.SetTxConfig(txConfig.Modem, txConfig.Power, txConfig.Fdev, txConfig.Bandwidth,
                      txConfig.DataRate, txConfig.CodeRate,
                      txConfig.PreambleLen, txConfig.FixLen,
                      txConfig.CrcOn, txConfig.FreqHopOn, txConfig.HopPeriod, txConfig.IqInverted, txConfig.Timeout);

    //   Radio.SetChannel(RF_FREQUENCY);
}

void ApplyRadioRXConfig() {
    Radio.SetRxConfig(rxConfig.Modem, rxConfig.Bandwidth, txConfig.DataRate, txConfig.CodeRate,
                      rxConfig.BandwidthAfc, rxConfig.PreambleLen,
                      rxConfig.SymbTimeout, rxConfig.FixLen, rxConfig.PayloadLen, rxConfig.CrcOn,
                      rxConfig.FreqHopOn, rxConfig.HopPeriod, rxConfig.IqInverted, rxConfig.RxContinuous);
}

void ApplyRadioConfig() {
    ApplyRadioTXConfig();
    ApplyRadioRXConfig();

    Radio.Rx(RX_TIMEOUT_VALUE);
}

void SetNewRFSettings(uint8_t *serialBuf, uint8_t bytesRead) {
    uint8_t i = 1;

    txConfig.Modem = (RadioModems_t)serialBuf[i++];
    txConfig.Power = serialBuf[i++];
    txConfig.Fdev = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);
    txConfig.Bandwidth = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);
    txConfig.DataRate = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);
    txConfig.CodeRate = serialBuf[i++];
    txConfig.PreambleLen = (serialBuf[i++] << 8) + (serialBuf[i++]);
    txConfig.FixLen = serialBuf[i++] > 0;
    txConfig.CrcOn = serialBuf[i++] > 0;
    txConfig.FreqHopOn = serialBuf[i++] > 0;
    txConfig.HopPeriod = serialBuf[i++];
    txConfig.IqInverted = serialBuf[i++] > 0;
    txConfig.Timeout = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);

    rxConfig.Modem = (RadioModems_t)serialBuf[i++];
    rxConfig.Bandwidth = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);
    rxConfig.DataRate = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);
    rxConfig.CodeRate = serialBuf[i++];
    rxConfig.BandwidthAfc = (serialBuf[i++] << 24) + (serialBuf[i++] << 16) + (serialBuf[i++] << 8) + (serialBuf[i++]);
    rxConfig.PreambleLen = (serialBuf[i++] << 8) + (serialBuf[i++]);
    rxConfig.FixLen = serialBuf[i++] > 0;
    rxConfig.PayloadLen = serialBuf[i++];
    rxConfig.CrcOn = serialBuf[i++] > 0;
    rxConfig.FreqHopOn = serialBuf[i++] > 0;
    rxConfig.HopPeriod = serialBuf[i++];
    rxConfig.IqInverted = serialBuf[i++] > 0;
    rxConfig.RxContinuous = serialBuf[i++] > 0;

    ApplyRadioConfig();

    printf("[CLI] %d, %d, %lu, %lu, %lu, %d, %d, %d, %d, %d, %d, %d, %lu, %d, %ld, %ld, %d, %ld, %d, %d, %d, %d, %d, %d, %d, %d", txConfig.Modem,
           txConfig.Power, txConfig.Fdev, txConfig.Bandwidth, txConfig.DataRate, txConfig.CodeRate, txConfig.PreambleLen, txConfig.FixLen, txConfig.CrcOn, txConfig.FreqHopOn, txConfig.HopPeriod, txConfig.IqInverted, txConfig.Timeout, rxConfig.Modem, rxConfig.Bandwidth, rxConfig.DataRate, rxConfig.CodeRate, rxConfig.BandwidthAfc, rxConfig.PreambleLen, rxConfig.FixLen, rxConfig.PayloadLen, rxConfig.CrcOn, rxConfig.FreqHopOn, rxConfig.HopPeriod, rxConfig.IqInverted, rxConfig.RxContinuous);
}

void UpdateRadioSpreadingFactor(uint spreadingFactor, bool reconnect) {
    txConfig.DataRate = spreadingFactor;
    rxConfig.DataRate = spreadingFactor;

    if (reconnect) {
        ApplyRadioConfig();
    }
}

void ProcessSpreadingFactorMessage(uint8_t unicodeValue, bool broadcastLoRa) {
    int spreadingFactor = MapSpreadingFactor(unicodeValue);
    if (spreadingFactor != -1) {
        if (broadcastLoRa) {
            TxSpreadingFactor(unicodeValue);
            printf("[CLI] Broadcasting SF %d\n\r", spreadingFactor);

            pendingConfigChange = true;
            UpdateRadioSpreadingFactor(spreadingFactor, false);
        } else {
            UpdateRadioSpreadingFactor(spreadingFactor, true);
        }

        printf("[CLI] Set Radio SF '%d' \n\r", spreadingFactor);
    } else {
        printf("[CLI] SF not 7,8,9,0,1,2(=12) skipped: '%c'\n\r", unicodeValue);
    }
}

void ApplyConfigIfPending() {
    if (!pendingConfigChange)
        return;
    pendingConfigChange = false;
    ApplyRadioConfig();
}

void ParseCliCMD() {
    //     printf("[CLI] command %c\n\r", serialBuf[0]);

    //     switch (serialBuf[0]) {
    //         // Set Spreading factor
    //         case 'S':
    //             if (bytesRead > 1) {
    //                 ProcessSpreadingFactorMessage(serialBuf[1], true);
    //             }
    //             break;

    //         // Ping
    //         case 'P':
    //             TxPing();
    //             break;

    //         // Send sequence test cmd
    //         case 'T':
    //             TxSequenceCommand((uint8_t *)serialBuf, bytesRead);
    //             break;

    //         // Send RF config packet
    //         case 'F':
    //             TxNewRFSettings((uint8_t *)serialBuf, bytesRead);
    //             break;

    //         case 'G':
    //             SetNewRFSettings((uint8_t *)serialBuf, bytesRead);
    //             break;

    //         default:
    //             printf("[cli] %c New command who this??", serialBuf[0]);
    //             break;
    //     }
}
