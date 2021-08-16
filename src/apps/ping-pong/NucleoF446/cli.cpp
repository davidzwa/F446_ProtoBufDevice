#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "delay.h"
#include "cli.h"
#include "tx.h"

#define SERIAL_BUFSIZE 256

char serialBuf[SERIAL_BUFSIZE];
uint8_t bytesRead = 0;
uint8_t msgSize;

bool pendingConfigChange = false;

RadioTXConfig_t txConfig = {
    .Modem = MODEM_LORA,
    .Power = TX_OUTPUT_POWER,
    .Fdev = 0,
    .Bandwidth = LORA_BANDWIDTH,
    .SpreadingFactor = LORA_SPREADING_FACTOR,
    .CodeRate = LORA_CODINGRATE,
    .PreambleLen = LORA_PREAMBLE_LENGTH,
    .FixLen = LORA_FIX_LENGTH_PAYLOAD_ON,
    .CrcOn = true,
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
    .CrcOn = true,
    .FreqHopOn = 0,
    .HopPeriod = 0,
    .IqInverted = LORA_IQ_INVERSION_ON,
    .RxContinuous = true};

void ApplyRadioTXConfig()
{
    Radio.SetTxConfig(txConfig.Modem, txConfig.Power, txConfig.Fdev, txConfig.Bandwidth,
                      txConfig.SpreadingFactor, txConfig.CodeRate,
                      txConfig.PreambleLen, txConfig.FixLen,
                      txConfig.CrcOn, txConfig.FreqHopOn, txConfig.HopPeriod, txConfig.IqInverted, txConfig.Timeout);
}

void ApplyRadioRXConfig()
{
    Radio.SetRxConfig(rxConfig.Modem, rxConfig.Bandwidth, txConfig.SpreadingFactor, txConfig.CodeRate,
                      rxConfig.BandwidthAfc, rxConfig.PreambleLen,
                      rxConfig.SymbTimeout, rxConfig.FixLen, rxConfig.PayloadLen, rxConfig.CrcOn,
                      rxConfig.FreqHopOn, rxConfig.HopPeriod, rxConfig.IqInverted, rxConfig.RxContinuous);
}

void ApplyRadioConfig()
{
    ApplyRadioTXConfig();
    ApplyRadioRXConfig();

    Radio.Rx(RX_TIMEOUT_VALUE);
}

void UpdateRadioSpreadingFactor(uint spreadingFactor, bool reconnect)
{
    txConfig.SpreadingFactor = spreadingFactor;
    rxConfig.SpreadingFactor = spreadingFactor;

    if (reconnect)
    {
        ApplyRadioConfig();
    }
}

int MapSpreadingFactor(uint8_t value)
{
    if (value == '7')
    {
        return 7;
    }
    else if (value == '8')
    {
        return 8;
    }
    else if (value == '9')
    {
        return 9;
    }
    else if (value == '0')
    {
        return 10;
    }
    else if (value == '1')
    {
        return 11;
    }
    else if (value == '2')
    {
        return 12;
    }

    return -1;
}

void ProcessSpreadingFactorMessage(uint8_t unicodeValue, bool broadcastLoRa)
{
    int spreadingFactor = MapSpreadingFactor(unicodeValue);
    if (spreadingFactor != -1)
    {
        if (broadcastLoRa)
        {
            TxSpreadingFactor(unicodeValue);
            printf("[CLI] Broadcasting SF %d\n\r", spreadingFactor);

            pendingConfigChange = true;
            UpdateRadioSpreadingFactor(spreadingFactor, false);
        }
        else
        {
            UpdateRadioSpreadingFactor(spreadingFactor, true);
        }

        printf("[CLI] Set Radio SF '%d' \n\r", spreadingFactor);
    }
    else
    {
        printf("[CLI] SF not 7,8,9,0,1,2(=12) skipped: '%c'\n\r", unicodeValue);
    }
}

void ApplyConfigIfPending()
{
    if (!pendingConfigChange)
        return;
    pendingConfigChange = false;
    ApplyRadioConfig();
}

void ParseCliCMD()
{

    switch (serialBuf[0])
    {
    // Set Spreading factor
    case 'S':
        if(bytesRead > 1){
            ProcessSpreadingFactorMessage(serialBuf[1], true);
        }
        break;

    // Ping
    case 'P':
        TxPing();
        break;

        // Set Spreading factor
    case 'T':
        if(bytesRead > 1){
            ProcessSpreadingFactorMessage(serialBuf[1], true);
        }
        break;

    default:
        break;
    }


    // if (value == 'P')
    // {
    //     TxPing();
    // }

    // if (value == 'T')
    // {
    //     char serialBuf[256];
    //     uint8_t bytesRead = 0;

    //     while(bytesRead < 2){

    //     }

    // }
}

#define SERIAL_END_BYTE '\n'

void CliProcess(Uart_t *uart)
{
    uint8_t byte;

    if (UartGetChar(uart, &byte) == 0)
    {

        if (bytesRead < SERIAL_BUFSIZE)
        {
            // Add new byte to buffer
            serialBuf[bytesRead++] = byte;

            // Look for end byte
            if (byte == SERIAL_END_BYTE)
            {

                // Parse msg
                if (bytesRead > 1)
                {
                    ParseCliCMD();
                }

                // Reset serial buffer
                bytesRead = 0;
            }
        }
        else
        {
            // ERROR serial overflow
            bytesRead = 0;
        }
    }
}