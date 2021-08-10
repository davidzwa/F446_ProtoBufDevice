/*!
 * \file      main.c
 *
 * \brief     Ping-Pong implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */

#define CRLF 1

#include <string.h>
#include "stdio.h"
#include "board.h"
#include "gpio.h"
#include "delay.h"
#include "timer.h"
#include "radio.h"
#include "config.h" // Radio config shared with CLI
#include "uart.h"
#include "cli.h"

typedef enum
{
    LOWPOWER,
    RX,
    RX_TIMEOUT,
    RX_ERROR,
    TX,
    TX_TIMEOUT,
} States_t;

#define RX_TIMEOUT_VALUE 1
#define BUFFER_SIZE 64 // Define the payload size here

const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";

uint16_t BufferSize = BUFFER_SIZE;
uint8_t Buffer[BUFFER_SIZE];

States_t State = LOWPOWER;

int8_t RssiValue = 0;
int8_t SnrValue = 0;

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * LED GPIO pins objects
 */
extern Gpio_t Led1;
extern Gpio_t Led2;

/*!
 * UART object used for command line interface handling
 */
extern Uart_t Uart2;

/*!
 * \brief Function to be executed on Radio Tx Done event
 */
void OnTxDone(void);

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout(void);

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout(void);

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError(void);

#define FIRMWARE_VERSION 0x01020000 // 1.2.0.0

#define GITHUB_VERSION 0x05000000 // 5.0.0.0

void DisplayAppInfo(const char *appName, const Version_t *appVersion, const Version_t *gitHubVersion)
{
    printf("\n###### ===================================== ######\n\n\r");
    printf("Application name   : %s\n\r", appName);
    printf("Application version: %d.%d.%d\n\r", appVersion->Fields.Major, appVersion->Fields.Minor, appVersion->Fields.Patch);
    printf("GitHub base version: %d.%d.%d\n\r", gitHubVersion->Fields.Major, gitHubVersion->Fields.Minor, gitHubVersion->Fields.Patch);
    printf("\n###### ===================================== ######\n\n\r");
}

/**
 * Main application entry point.
 */
int main(void)
{
    bool isMaster = true;
    uint8_t i;

    // Target board initialization
    BoardInitMcu();
    BoardInitPeriph();

    const Version_t appVersion = {.Value = FIRMWARE_VERSION};
    const Version_t gitHubVersion = {.Value = GITHUB_VERSION};
    DisplayAppInfo("pingh-pongh Tomato-potato",
                   &appVersion,
                   &gitHubVersion);

    printf("Radio initializing\n\r");

    // Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);

    RadioState_t state = Radio.GetStatus();
    printf("Radio state %d\n\r", state);

    printf("Radio init done\n\r");

    state = Radio.GetStatus();
    Radio.SetChannel(RF_FREQUENCY);

    printf("Radio state %d\n\r", state);

    printf("Radio set channel to %d done\n\r", RF_FREQUENCY);

    printf("Radio state %d\n\r", state);

#if defined(USE_MODEM_LORA)

    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    Radio.SetMaxPayloadLength(MODEM_LORA, BUFFER_SIZE);

#elif defined(USE_MODEM_FSK)

    Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
                      FSK_DATARATE, 0,
                      FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, 0, 3000);

    Radio.SetRxConfig(MODEM_FSK, FSK_BANDWIDTH, FSK_DATARATE,
                      0, FSK_AFC_BANDWIDTH, FSK_PREAMBLE_LENGTH,
                      0, FSK_FIX_LENGTH_PAYLOAD_ON, 0, true,
                      0, 0, false, true);

    Radio.SetMaxPayloadLength(MODEM_FSK, BUFFER_SIZE);

#else
#error "Please define a frequency band in the compiler options."
#endif

    printf("Radio started. Listening\n\r");

    Radio.Rx(RX_TIMEOUT_VALUE);

    // while (1)
    // {
    //     // Send the next PING frame
    //     Buffer[0] = 'P';
    //     Buffer[1] = 'I';
    //     Buffer[2] = 'N';
    //     Buffer[3] = 'G';
    //     // We fill the buffer with numbers for the payload
    //     for (i = 4; i < BufferSize; i++)
    //     {
    //         Buffer[i] = i - 4;
    //     }

    //     Radio.Send(Buffer, BufferSize);
    //     DelayMs(1000);
    //     printf("PINGED\n\r");
    //     DelayMs(100);
    // }

    printf("Radio going into ping-pong mode.\n\r");

    while (1)
    {
        switch (State)
        {
        case RX:
            if (isMaster == true)
            {
                if (BufferSize > 0)
                {
                    if (strncmp((const char *)Buffer, (const char *)PongMsg, 4) == 0)
                    {
                        // Indicates on a LED that the received frame is a PONG
                        GpioToggle(&Led1);

                        // Send the next PING frame
                        Buffer[0] = 'P';
                        Buffer[1] = 'I';
                        Buffer[2] = 'N';
                        Buffer[3] = 'G';
                        // We fill the buffer with numbers for the payload
                        for (i = 4; i < BufferSize; i++)
                        {
                            Buffer[i] = i - 4;
                        }
                        DelayMs(1);
                        printf("PINGED\n\r");
                        Radio.Send(Buffer, BufferSize);
                    }
                    else if (strncmp((const char *)Buffer, (const char *)PingMsg, 4) == 0)
                    { // A master already exists then become a slave
                        isMaster = false;
                        GpioToggle(&Led2); // Set LED off
                        Radio.Rx(RX_TIMEOUT_VALUE);
                    }
                    else // valid reception but neither a PING or a PONG message
                    {    // Set device as master ans start again
                        isMaster = true;
                        Radio.Rx(RX_TIMEOUT_VALUE);
                    }
                }
            }
            else
            {
                if (BufferSize > 0)
                {
                    if (strncmp((const char *)Buffer, (const char *)PingMsg, 4) == 0)
                    {
                        // Indicates on a LED that the received frame is a PING
                        GpioToggle(&Led1);

                        // Send the reply to the PONG string
                        Buffer[0] = 'P';
                        Buffer[1] = 'O';
                        Buffer[2] = 'N';
                        Buffer[3] = 'G';
                        // We fill the buffer with numbers for the payload
                        for (i = 4; i < BufferSize; i++)
                        {
                            Buffer[i] = i - 4;
                        }
                        DelayMs(1);
                        Radio.Send(Buffer, BufferSize);
                        printf("PONGED\n\r");
                    }
                    else // valid reception but not a PING as expected
                    {    // Set device as master and start again
                        isMaster = true;
                        Radio.Rx(RX_TIMEOUT_VALUE);
                    }
                }
            }
            State = LOWPOWER;
            break;
        case TX:
            // Indicates on a LED that we have sent a PING [Master]
            // Indicates on a LED that we have sent a PONG [Slave]
            GpioToggle(&Led2);
            Radio.Rx(RX_TIMEOUT_VALUE);
            printf("TX\n\r");
            State = LOWPOWER;
            break;
        case RX_TIMEOUT:
        case RX_ERROR:
            printf("TX error or timeout\n\r");
            if (isMaster == true)
            {
                // Send the next PING frame
                Buffer[0] = 'P';
                Buffer[1] = 'I';
                Buffer[2] = 'N';
                Buffer[3] = 'G';
                for (i = 4; i < BufferSize; i++)
                {
                    Buffer[i] = i - 4;
                }
                DelayMs(1);
                Radio.Send(Buffer, BufferSize);
            }
            else
            {
                Radio.Rx(RX_TIMEOUT_VALUE);
            }
            State = LOWPOWER;
            break;
        case TX_TIMEOUT:
            printf("tx\n\r");
            Radio.Rx(RX_TIMEOUT_VALUE);
            State = LOWPOWER;
            break;
        case LOWPOWER:
        default:
            // Set low power
            CliProcess( &Uart2 );
            break;
        }

        BoardLowPowerHandler();
        // Process Radio IRQ
        if (Radio.IrqProcess != NULL)
        {
            Radio.IrqProcess();
        }
    }
}

void OnTxDone(void)
{
    printf("tx done\n\r");
    Radio.Sleep();
    State = TX;
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    printf("rx done\n\r");
    Radio.Sleep();
    BufferSize = size;
    memcpy(Buffer, payload, BufferSize);
    RssiValue = rssi;
    SnrValue = snr;
    State = RX;
}

void OnTxTimeout(void)
{
    printf("tx timeout\n\r");
    Radio.Sleep();
    State = TX_TIMEOUT;
}

void OnRxTimeout(void)
{
    printf("rx timeout\n\r");
    Radio.Sleep();
    State = RX_TIMEOUT;
}

void OnRxError(void)
{
    printf("error\n\r");
    Radio.Sleep();
    State = RX_ERROR;
}
