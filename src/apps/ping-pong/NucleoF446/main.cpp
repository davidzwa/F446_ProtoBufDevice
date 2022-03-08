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

    // unsigned int prim_poly = 0x11D;
    // galois::GaloisField gf(8, prim_poly);
    
    // This must be called remotely/over UART
    // ClearStorage();

    // Uart debugging
    // const galois::GFSymbol unity(1);
    // const galois::GFSymbol val(0x04);
    // const galois::GFSymbol val2(0xdb);
    // auto result = gf.div(unity, val);
    // UartDebug("Unit", unity, 4);
    // UartDebug("Val", val, 3);
    // UartDebug("MInv", result, 4);
    // UartDebug("Mult", gf.mul(result, val), 4);
    // UartDebug("Mul2", gf.mul(result, val2), 4);

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
