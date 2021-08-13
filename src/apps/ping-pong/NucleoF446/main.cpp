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
#include "uart.h"

#include "radio.h"
#include "tx.h"
#include "rx.h"
#include "config.h" // Radio config shared with CLI
#include "config_personal.h"
#include "cli.h"

bool isGateway = true;
bool hasNewPacket = false;

int8_t RssiValue = 0;
int8_t SnrValue = 0;

extern uint16_t BufferSize;
extern uint8_t Buffer[BUFFER_SIZE];

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
 * \brief Radio interupts
 */
void OnTxDone(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);
void OnRxTimeout(void);
void OnRxError(void);


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
    // Target board initialization
    BoardInitMcu();
    BoardInitPeriph();

    const Version_t appVersion = {.Value = FIRMWARE_VERSION};
    const Version_t gitHubVersion = {.Value = GITHUB_VERSION};
    DisplayAppInfo("Tomato-potato",
                   &appVersion,
                   &gitHubVersion);

    if (isGateway == true){
        printf("I'm a gateway\n\r");
    }else{
        printf("I'm a endNode\n\r");
    }

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

    Radio.SetChannel(RF_FREQUENCY);
    state = Radio.GetStatus();
    printf("Radio state %d\n\r", state);
    printf("Radio set channel to %d done\n\r", RF_FREQUENCY);

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

    printf("Started radio listening\n\r");
    Radio.Rx(RX_TIMEOUT_VALUE);
 
    while (1)
    {
        if(hasNewPacket){
            if (isGateway == true)
            {
                printf("[Gateway] Received packet:\n\r");
                //TODO Send received data to pc

                for(int i=0; i<bufferSize; i++){
                    printf("0x%02X ", buffer[i] );
                }

                printf("\n\rbufferSize: %d\n\r", bufferSize);
                printf("RssiValue: %d\n\r", RssiValue);
                printf("SnrValue: %d\n\r\n\r", SnrValue);

                // Listen for next radio packet
                Radio.Rx(RX_TIMEOUT_VALUE);
            }
            else
            {
                if (bufferSize > 0)
                {
                    if (IsSpreadingFactorConfig((const char *)buffer))
                    {
                        LoRaProcessMode((const char *)buffer);
                    }
                    else // valid reception but not config as expected
                    {
                        Radio.Rx(RX_TIMEOUT_VALUE);
                    }
                }
            }
            // Reset has new packet flag
            hasNewPacket = false;
        }
        

        CliProcess(&Uart2);

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
    if (isGateway == true)
    {
        // Listen for next radio packet
        Radio.Rx(RX_TIMEOUT_VALUE);
    }else{
	    ApplyConfigIfPending();
	    Radio.Sleep();
	}

    printf("[Main] tx done\n\r");
}


void OnTxTimeout(void)
{
	if (isGateway == true)
    {
        // Listen for next radio packet
        Radio.Rx(RX_TIMEOUT_VALUE);
    }
    printf("[Main] tx timeout\n\r");
    ApplyConfigIfPending();
    Radio.Sleep();
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    if (IsSpreadingFactorConfig((const char *)payload))
    {
        LoRaProcessMode((const char *)payload);
    }

    printf("[Main] rx done\n\r");
    Radio.Sleep();
    bufferSize = size;
    memcpy(buffer, payload, bufferSize);
    RssiValue = rssi;
    SnrValue = snr;
    
    hasNewPacket = true;
}

void OnRxTimeout(void)
{
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxError(void)
{
    printf("[Main] error\n\r");
    Radio.Rx(RX_TIMEOUT_VALUE);
}
