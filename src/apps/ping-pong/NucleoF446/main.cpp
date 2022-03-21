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

#include "Crc8.h"
#include "board.h"
#include "cli.h"
#include "config.h"
#include "delay.h"
#include "measurements.h"
#include "nvmm.h"
#include "radio_config.h"
#include "radio_phy.h"
#include "tasks.h"
#include "utils.h"
#include "gpio.h"

/**
 * @brief Push button on PC13 (pin 2)
 *
 */
Gpio_t button;

__attribute__((long_call, section(".code_in_ram"))) void foo(void) {
    // Do something here
    UartDebug("RAMFUNC", 0, 8);
}

void ButtonCallback(void* context) {
    UartDebug("PUSH-BUTTON", 0, 12);

    decoder.AutoTerminateRlnc();

    foo();
}

int main(void) {
    BoardInitMcu();
    BoardInitPeriph();
    InitCli(true);
    InitializeMeasurements();
    InitRadioTxConfigLoRa();
    InitRadioRxConfigLoRa();
    InitRadioPhy();
    InitTimedTasks();

    UartSendBoot();

    // ApplyRadioConfig();
    UartDebug(__TIMESTAMP__, 0, sizeof(__TIMESTAMP__));
    
    GpioInit(&button, PC_13, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioSetInterrupt(&button, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, &ButtonCallback);

    uint32_t output;
    ReadMeasurement(0, &output);
    UartDebug("FLASH", output, 12);

    // CRC check
    // uint8_t values[] = {0xFF, 0x12, 0x34, 0x00};
    // auto outcome = ComputeChecksum(values, sizeof(values));
    // UartDebug("CRC", outcome, 3);

    // uint8_t values2[] = {0x00, 0x12, 0x34, 0x00};
    // outcome = ComputeChecksum(values2, sizeof(values2));
    // UartDebug("CRC", outcome, 3);

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
            if (IsCrcValid()) {
                ProcessCliCommand();
            }
            else {
                UartDebug("CRC-FAIL", 400, 8);
                ResetCrcFailure();
            }
        }
    }
}
