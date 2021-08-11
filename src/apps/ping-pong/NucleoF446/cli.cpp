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

void CliProcess(Uart_t *uart)
{
    uint8_t data = 0;

    if (UartGetChar(uart, &data) == 0)
    {
        if (data == '\x1B')
        {
            // Escape character has been received
            printf("ESC... (options: S (SF), TODO)");
            while (UartGetChar(uart, &data) != 0)
            {
            }
            printf("%c\n\r", data);

            if (data == 'S')
            {
                // S character has been received for Spreading Facto
                data = 0;
                while (UartGetChar(uart, &data) != 0)
                {
                }

                if (data == '7')
                {
                    SetRadioConfig(7);
                }
                else if (data == '8')
                {
                    SetRadioConfig(8);
                }
                else if (data == '9')
                {
                    SetRadioConfig(9);
                }
                else if (data == '0')
                {
                    SetRadioConfig(10);
                }
                else if (data == '1')
                {
                    SetRadioConfig(11);
                }
                else if (data == '2')
                {
                    SetRadioConfig(12);
                }
                else
                {
                    printf("SF not 7,8,9 or 0(=10), 1(=11) or 2(12), skipped\n\r");
                }
                printf("CLI done\n\r");
            }
        }
    }
}