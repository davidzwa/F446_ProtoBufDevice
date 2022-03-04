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
 *  Date 20 Sept 2021
 *
 *  Description:
 *   Ping pong application for experimenting with LoRa
 *   Includes a UART CLI
 */

#include "board.h"
#include "cli.h"
#include "config.h"
#include "delay.h"
#include "measurements.h"
#include "nvmm.h"
#include "radio_phy.h"
#include "tasks.h"
#include "utils.h"

int main(void) {
    BoardInitMcu();
    BoardInitPeriph();
    InitCli(true);
    InitializeMeasurements();
    UartSendBoot();
    InitRadioConfig();
    InitTimedTasks();
    InitRadioPhy();

    unsigned int prim_poly[9] = {1, 0, 0, 0, 1, 1, 1, 0, 1};
    galois::GaloisField gf(8, prim_poly);
    // Reused symbols in decoding
    const galois::GaloisFieldElement pivot(&gf, 1);
    // const galois::GaloisFieldElement val(&gf, 4);
    // auto result = pivot / val;

    // This must be called remotely/over UART
    // ClearStorage();

    // Uart debugging
    for (int i = 1; i<255; i++) {
        const galois::GaloisFieldElement val(&gf, i);
        auto result = pivot / val;
        UartDebug("1/VAL", result.poly(), 5);
        DelayMs(1);
    }
    
    // UartDebug("1234", 0, 4);
    // UartDebug("1234", 0, 4);
    // UartDebug("1234", 0, 4);

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
