/*!
 * \file      cli.h
 *
 * \brief     Command Line Interface handling definition
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
 *              (C)2013-2020 Semtech
 *
 * \endcode
 */

#include "uart.h"
#include "config.h"
#include "cli_commands.h"

#ifndef CLI_H
#define CLI_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
 * Process characters received on the serial interface
 * \remark Characters sequence 'ESC' + 'N' execute a NVM factory reset
 *         All other sequences are ignored
 *
 * \param [IN] uart UART interface object used by the command line interface
 */

    void ProcessSpreadingFactorMessage(uint8_t value, bool broadcastLoRa);
    SequenceCommand_t ProcessSequenceCommand(const char *buffer);
    void ApplyConfigIfPending();
    void CliProcess(Uart_t *uart);

#ifdef __cplusplus
}
#endif

#endif // CLI_H
