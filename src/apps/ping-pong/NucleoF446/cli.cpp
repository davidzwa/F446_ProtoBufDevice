#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "cli.h"
#include "config.h"

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

    // Radio.SetMaxPayloadLength(MODEM_LORA, BUFFER_SIZE);
}

void CliProcess(Uart_t *uart)
{
    uint8_t data = 0;

    if (UartGetChar(uart, &data) == 0)
    {
        if (data == '\x1B')
        {
            // Escape character has been received
            printf("ESC + ");
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
                else if (data == '10')
                {
                    SetRadioConfig(9);
                }
                else
                {
                    printf("SF not 7 to 10, skipped\n\r");
                }
                printf("Cli received info\n\r");
            }
        }
    }
}