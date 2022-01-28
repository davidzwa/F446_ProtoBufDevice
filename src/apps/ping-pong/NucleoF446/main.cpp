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
#include "nvmm.h"
#include "radio_phy.h"
#include "measurements_nvmm.h"
#include "tasks.h"
#include "utils.h"


int main(void) {
    BoardInitMcu();
    BoardInitPeriph();
    InitCli(true);
    UartSendBoot();
    InitRadioConfig();
    InitTimedTasks();
    InitRadioPhy();

    uint16_t status = NvmmWriteVar32(1, (uint32_t)0x1234);
    if (status != 0) {
        throw 1;
    }
    
    uint32_t readData;
    uint16_t result = NvmmReadVar32(1, &readData);
    if (result != 0) {
        throw 1;
    }
    if (readData != 0x1234) {
        throw 2;
    }

    NvmmClear();
    
    uint32_t resultMeasurements = GetMeasurementCount();
    if (resultMeasurements == CORRUPT_MEASUREMENT_COUNTERS) {
        throw 3;
    }

        Radio.Rx(0);
    while (1) {
        // Process Radio IRQ
        if (Radio.IrqProcess != NULL) {
            Radio.IrqProcess();
        }

        if (IsCliCommandReady()) {
            ProcessCliCommand();
        }
    }
}
