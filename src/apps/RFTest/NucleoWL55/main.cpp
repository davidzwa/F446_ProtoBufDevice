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

#include "board.h"
#include "cli.h"
#include "config.h"  // Radio config shared with CLI
#include "config_personal.h"
#include "delay.h"
#include "gpio.h"
#include "radio.h"
#include "rx.h"
#include "stdio.h"
#include "uart.h"
#include "utils.h"

#include "main.h"

int8_t RssiValue = 0;
int8_t SnrValue = 0;

bool isExecutingCMD = false;

extern uint16_t msgSize;
extern uint8_t buffer[BUFFER_SIZE];

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

void DisplayAppInfo(const char *appName, const Version_t *appVersion, const Version_t *gitHubVersion) {
    printf("\n###### ===================================== ######\n\n\r");
    printf("Application name   : %s\n\r", appName);
    printf("Application version: %d.%d.%d\n\r", appVersion->Fields.Major, appVersion->Fields.Minor, appVersion->Fields.Patch);
    printf("GitHub base version: %d.%d.%d\n\r", gitHubVersion->Fields.Major, gitHubVersion->Fields.Minor, gitHubVersion->Fields.Patch);
    printf("\n###### ===================================== ######\n\n\r");
}

/**
 * Main application entry point.
 */
int main(void) {
    // Target board initialization
    BoardInitMcu();
    BoardInitPeriph();

    DeviceId_t deviceId = GetDeviceId();
    printf("id %lu %lu %lu\n\r", deviceId.id0, deviceId.id1, deviceId.id2);

    const Version_t appVersion = {.Value = FIRMWARE_VERSION};
    const Version_t gitHubVersion = {.Value = GITHUB_VERSION};
    DisplayAppInfo("Tomato-potato",
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

    while (1) {
        CliProcess(&Uart2);

        TxTestProcess();

        // Process Radio IRQ
        if (Radio.IrqProcess != NULL) {
            Radio.IrqProcess();
        }
    }
}

void OnTxDone(void) {
    printf("[Main] tx done\n\r");

    ApplyConfigIfPending();

    if (!isExecutingCMD) {
        Radio.Rx(RX_TIMEOUT_VALUE);
    } else {
        Radio.Sleep();
    }
}

void OnTxTimeout(void) {
    printf("[Main] tx timeout\n\r");

    ApplyConfigIfPending();

    if (!isExecutingCMD) {
        Radio.Rx(RX_TIMEOUT_VALUE);
    } else {
        Radio.Sleep();
    }
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
    printf("[Main] rx done\n\r");

    msgSize = size;
    memcpy(buffer, payload, msgSize);
    RssiValue = rssi;
    SnrValue = snr;

    printf("[Main]");
    for (int i = 0; i < msgSize; i++) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n\r[Main] MsgSize: %d RssiValue: %d SnrValue: %d\n\r", msgSize, rssi, snr);

    parseMsg(buffer, msgSize);

    // Listen for next radio packet
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxTimeout(void) {
    printf("[Main] OnRxTimeout\n\r");
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxError(void) {
    printf("[Main] error\n\r");
    Radio.Rx(RX_TIMEOUT_VALUE);
}
