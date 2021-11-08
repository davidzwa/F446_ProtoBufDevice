/*
*    __________ ____
*   |__  / ____|  _ \ 
*     / /|  _| | | | |
*    / /_| |___| |_| |
*   /____|_____|____/ 
*  Copyright (C) 2020 - 2021
* 
*  License:  Revised BSD License, see LICENSE.TXT file included in the project
*  Authors:  David Zwart (ZED), Niels Hokke (ZED)
*  Version: 0.1.1
*  Date 20 Sept 2021
* 
*  Description:
*   Ping pong application for experimenting with LoRa
*   Includes a UART CLI
*/

#include <string.h>

#include "board.h"
#include "cli.h"
#include "config.h"
#include "delay.h"
#include "radio.h"
#include "rx.h"
#include "tasks.h"
#include "utils.h"

int8_t lastRssiValue = 0;
int8_t lastSnrValue = 0;

bool isExecutingCMD = false;

extern uint16_t msgSize;
extern uint8_t buffer[BUFFER_SIZE];

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*!
 * \brief Radio interupts
 */
void OnTxDone(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);
void OnRxTimeout(void);
void OnRxError(void);

/**
 * Main application entry point.
 */
int main(void) {
    InitRadioConfig();
    BoardInitMcu();
    BoardInitPeriph();
    InitCli(true);
    InitTimedTasks();

    UartSendBoot();

    // Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);
    printf("Radio init done\n");
    PrintSettings();

    Radio.SetChannel(RF_FREQUENCY);
    RadioState_t state = Radio.GetStatus();
    printf("Radio state %d\n", state);
    printf("Radio set channel to %d done\n", RF_FREQUENCY);

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

    printf("Started RX radio\n");
    Radio.Rx(RX_TIMEOUT_VALUE);

    while (1) {
        // Process Radio IRQ
        if (Radio.IrqProcess != NULL) {
            Radio.IrqProcess();
        }
    }
}

void OnTxDone(void) {
    printf("[Main] tx done\n");

    ApplyConfigIfPending();

    if (!isExecutingCMD) {
        Radio.Rx(RX_TIMEOUT_VALUE);
    } else {
        Radio.Sleep();
    }
}

void OnTxTimeout(void) {
    printf("[Main] tx timeout\n");

    ApplyConfigIfPending();

    if (!isExecutingCMD) {
        Radio.Rx(RX_TIMEOUT_VALUE);
    } else {
        Radio.Sleep();
    }
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
    printf("[Main] rx done\n");

    msgSize = size;
    memcpy(buffer, payload, msgSize);
    lastRssiValue = rssi;
    lastSnrValue = snr;

    printf("[Main]");
    for (int i = 0; i < msgSize; i++) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n[Main] MsgSize: %d RssiValue: %d SnrValue: %d\n", msgSize, rssi, snr);

    parseMsg(buffer, msgSize);

    // Listen for next radio packet
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxTimeout(void) {
    printf("[Main] OnRxTimeout\n");
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxError(void) {
    printf("[Main] error\n");
    Radio.Rx(RX_TIMEOUT_VALUE);
}
