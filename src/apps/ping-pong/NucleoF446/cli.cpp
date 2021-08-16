#include "cli.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "delay.h"
#include "tx.h"
#include "utils.h"

#define SERIAL_BUFSIZE 256

char serialBuf[SERIAL_BUFSIZE];
uint8_t bytesRead = 0;
uint8_t msgSize;

bool pendingConfigChange = false;
int testMessageLeftOverCount = -1;
SequenceCommand_t lastSequenceCommand;

RadioTXConfig_t txConfig = {
    .Modem = MODEM_LORA,
    .Power = TX_OUTPUT_POWER,
    .Fdev = 0,
    .Bandwidth = LORA_BANDWIDTH,
    .SpreadingFactor = LORA_SPREADING_FACTOR,
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
    .SpreadingFactor = LORA_SPREADING_FACTOR,
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

void ApplyRadioTXConfig() {
    Radio.SetTxConfig(txConfig.Modem, txConfig.Power, txConfig.Fdev, txConfig.Bandwidth,
                      txConfig.SpreadingFactor, txConfig.CodeRate,
                      txConfig.PreambleLen, txConfig.FixLen,
                      txConfig.CrcOn, txConfig.FreqHopOn, txConfig.HopPeriod, txConfig.IqInverted, txConfig.Timeout);
}

void ApplyRadioRXConfig() {
    Radio.SetRxConfig(rxConfig.Modem, rxConfig.Bandwidth, txConfig.SpreadingFactor, txConfig.CodeRate,
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
    txConfig.SpreadingFactor = spreadingFactor;
    rxConfig.SpreadingFactor = spreadingFactor;

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

SequenceCommand_t ProcessSequenceCommand(const char *buffer) {
    int offset = 1;
    uint16_t messageCount = (buffer[offset + 1] << 8) + buffer[offset];
    offset += 2;
    uint16_t intervalMs = (buffer[offset + 1] << 8) + buffer[offset];
    offset += 2;
    uint32_t deviceId = (buffer[offset + 3] << 24) + (buffer[offset + 2] << 16) + (buffer[offset + 1] << 8) + buffer[offset];

    DeviceId_t currentDeviceId = GetDeviceId();

    if (currentDeviceId.id0 != deviceId) {
        printf("Device id0 %lu was not equal to %lu! Command ignored.\n\r", currentDeviceId.id0, deviceId);
    } else {
        if (intervalMs < 150) {
            printf("Device ID recognized, but intervalMS %d was too low (<150). Ignoring command", intervalMs);
        } else {
            testMessageLeftOverCount = messageCount;
            lastSequenceCommand = {
                .messageCount = messageCount,
                .intervalMs = intervalMs,
                .deviceId = deviceId};
            printf("Device id %lu recognized. Test Packets: %d, interval: %d ms\n\r", deviceId, messageCount, intervalMs);
        }
    }

    return lastSequenceCommand;
}

void ApplyConfigIfPending() {
    if (!pendingConfigChange)
        return;
    pendingConfigChange = false;
    ApplyRadioConfig();
}

SequenceCommand_t command = {
    .messageCount = 1,
    .intervalMs = 1500,
    .deviceId = 4456526};

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

        // Set Spreading factor
        case 'T':
            TxSequenceCommand(command);
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

            // printf("[UART] received: %d\n\r", byte);

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