#include "cli.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "delay.h"
#include "tx.h"
#include "utils.h"

#define SERIAL_BUFSIZE 256

uint8_t serialBuf[SERIAL_BUFSIZE];
uint8_t bytesRead = 0;

bool pendingConfigChange = false;
int testMessageLeftOverCount = -1;
SequenceCommand_t lastSequenceCommand;

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

#elif defined(USE_MODEM_FSK)
RadioTXConfig_t txConfig = {
    .Modem = MODEM_FSK,
    .Power = TX_OUTPUT_POWER,
    .Fdev = FSK_FDEV,
    .Bandwidth = FSK_BANDWIDTH,
    .DataRate = FSK_DATARATE,
    .CodeRate = 0,
    .PreambleLen = FSK_PREAMBLE_LENGTH,
    .FixLen = FSK_FIX_LENGTH_PAYLOAD_ON,
    .CrcOn = false,  // true,
    .FreqHopOn = 0,
    .HopPeriod = 0,
    .IqInverted = 0,
    .Timeout = true};

RadioRXConfig_t rxConfig = {
    .Modem = MODEM_FSK,
    .Bandwidth = FSK_BANDWIDTH,
    .DataRate = FSK_DATARATE,
    .CodeRate = 0,
    .BandwidthAfc = FSK_AFC_BANDWIDTH,
    .PreambleLen = FSK_PREAMBLE_LENGTH,
    .FixLen = FSK_FIX_LENGTH_PAYLOAD_ON,
    .PayloadLen = 0,
    .CrcOn = false,  // true,
    .FreqHopOn = 0,
    .HopPeriod = 0,
    .IqInverted = false,
    .RxContinuous = true};

#else
#error "Please define a modem FSK or LORA in the compiler options."
#endif

void ApplyRadioTXConfig() {
    Radio.SetTxConfig(txConfig.Modem, txConfig.Power, txConfig.Fdev, txConfig.Bandwidth,
                      txConfig.DataRate, txConfig.CodeRate,
                      txConfig.PreambleLen, txConfig.FixLen,
                      txConfig.CrcOn, txConfig.FreqHopOn, txConfig.HopPeriod, txConfig.IqInverted, txConfig.Timeout);
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
    switch (serialBuf[0]) {
        // Set Spreading factor
        case 'S':
            if (bytesRead > 1) {
                ProcessSpreadingFactorMessage(serialBuf[1], true);
            }
            break;

        // Ping
        case 'P':
            TxPing();
            break;

        // Send sequence test cmd
        case 'T':
            TxSequenceCommand((uint8_t *)serialBuf, bytesRead);
            break;

        default:
            break;
    }
}

#define SERIAL_END_BYTE '\r'

void CliProcess(Uart_t *uart) {
    uint8_t byte;

    // Try to get new byte from uart buffer
    if (UartGetChar(uart, &byte) == 0) {
        if (bytesRead < SERIAL_BUFSIZE) {
            // Add new byte to buffer
            serialBuf[bytesRead++] = byte;

            printf("[cli] uart received: %d\n\r", byte);

            // Look for end byte
            if (byte == SERIAL_END_BYTE) {
                // Parse msg
                if (bytesRead > 1) {
                    ParseCliCMD();
                }

                // Reset serial buffer
                bytesRead = 0;
            }
        } else {
            // ERROR serial overflow
            bytesRead = 0;
        }
    }
}