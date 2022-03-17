/*
*    __________ ____
*   |__  / ____|  _ \ 
*     / /|  _| | | | |
*    / /_| |___| |_| |
*   /____|_____|____/ 
*  Copyright (C) 2020 - 2022
* 
*  License:  Revised BSD License, see LICENSE.TXT file included in the project
*  Authors:  David Zwart (ZED), Niels Hokke (ZED)
*  Version: 0.1.1
*  Date 6 Nov 2021
* 
*  Description:
*   CLI interface using UART
*/

#include <stdio.h>
#include "config.h"
#include "FieldStringBytes.h"

#ifndef CLI_H
#define CLI_H

#ifdef __cplusplus
extern "C" {
#endif

void InitCli(bool withISR);

bool IsCrcValid();
void ResetCrcFailure();
bool IsCliCommandReady();
void ProcessCliCommand();

// void UpdateRadioSpreadingFactor(uint8_t spreadingFactorRx, uint8_t spreadingFactorTx, bool reconnect);
// void ApplyRadioConfig ();
// void ApplyConfigIfPending();
// void SetTxPower(int8_t power);

void UartSendBoot();
void UartSendAck(uint8_t sequenceNumber);
void UartSendDecodingResult(bool success, uint8_t matrixRank, uint8_t firstDecodedNumber, uint8_t lastDecodedNumber);
void UartThrow(const char* payload, size_t length);
void UartDebug(const char* payload, uint32_t code, size_t length);
void UartSendLoRaRxError();
void UartSendLoRaRx(LORA_MSG_TEMPLATE& nessage, int16_t rssi, int8_t snr, bool isMeasurementFragment);
void PrintSettings();

#ifdef __cplusplus
}
#endif

#endif  // CLI_H
