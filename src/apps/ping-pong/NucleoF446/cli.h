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

#include "config.h"
#include "uart.h"

#ifndef CLI_H
#define CLI_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Process characters received on the serial interface
 * \remark Characters sequence 'ESC' + 'N' execute a NVM factory reset
 *         All other sequences are ignored
 *
 * \param [IN] uart UART interface object used by the command line interface
 */

void InitCli(bool withISR);
void ProcessSpreadingFactorMessage(uint8_t value, bool broadcastLoRa);
void ApplyConfigIfPending();
void SetNewRFSettings(uint8_t *serialBuf, uint8_t bytesRead);

#ifdef __cplusplus
}
#endif

#endif  // CLI_H
