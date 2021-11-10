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
*  Date 6 Nov 2021
* 
*  Description:
*   CLI interface using UART
*/

#include <stdio.h>

#ifndef CLI_H
#define CLI_H

#ifdef __cplusplus
extern "C" {
#endif

void InitCli(bool withISR);
void InitRadioConfig();
void UpdateRadioSpreadingFactor(uint8_t spreadingFactor, bool reconnect);
void ApplyConfigIfPending();
void UartSendBoot();
void PrintSettings();

#ifdef __cplusplus
}
#endif

#endif  // CLI_H
