#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "delay.h"
#include "cli.h"
#include "tx.h"

void SetRadioConfig(uint spreadingFactor)
{
    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      spreadingFactor, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, spreadingFactor,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    printf("SF %d set\n\r", spreadingFactor);

    Radio.Rx(RX_TIMEOUT_VALUE);
    TxPing();
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
            printf("[CLI] Broadcasting SF %c\n\r", spreadingFactor);            
            DelayMs(1000);
        }
        SetRadioConfig(spreadingFactor);
        printf("[CLI] Set Radio SF '%c'\n\r", spreadingFactor);
    }
    else
    {
        printf("[CLI] SF not 7,8,9,0,1,2(=12) skipped: '%c'\n\r", unicodeValue);
    }
}

void CliProcess(Uart_t *uart)
{
    uint8_t value = 0;

    if (UartGetChar(uart, &value) == 0)
    {
        if (value == 'S')
        {
            // S character has been received for Spreading Facto
            value = 0;
            while (UartGetChar(uart, &value) != 0)
            {
            }

            ProcessSpreadingFactorMessage(value, true);
        }

        if (value == 'P') {
            TxPing();
        }

        printf("[CLI] Done\n\r");
    }
}