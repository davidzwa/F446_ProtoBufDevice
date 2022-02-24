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
#include "measurements.h"
#include "nvmm.h"
#include "radio_phy.h"
#include "tasks.h"
#include "utils.h"

// #include "GaloisFieldElement.h"

int main(void) {
    BoardInitMcu();
    BoardInitPeriph();
    InitCli(true);
    InitializeMeasurements();
    UartSendBoot();
    InitRadioConfig();
    InitTimedTasks();
    InitRadioPhy();

    // This must be called remotely/over UART
    // ClearStorage();

    /*
    p(x) = 1x^8+1x^7+0x^6+0x^5+0x^4+0x^3+1x^2+1x^1+1x^0
           1    1    0    0    0    0    1    1    1
    */
    // unsigned int prim_poly[9] = {1, 1, 1, 0, 0, 0, 0, 1, 1};
    // // A Galois Field of type GF(2^8)
    // galois::GaloisField gf(8, prim_poly);
    // galois::GaloisFieldElement element1(&gf, 1);
    // galois::GaloisFieldElement element2(&gf, 2);
    // UartDebug("GF calc", (element1 * element2).poly(), 8);

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
