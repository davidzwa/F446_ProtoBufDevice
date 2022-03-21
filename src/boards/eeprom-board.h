/*!
 * \file      eeprom-board.h
 *
 * \brief     Target board EEPROM driver implementation
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
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 */
#ifndef __EEPROM_BOARD_H__
#define __EEPROM_BOARD_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "utilities.h"

uint16_t EepromMcuInit(void);
LmnStatus_t EepromMcuClearPage(uint8_t pageId);
LmnStatus_t EepromMcuWriteVariable32(uint8_t pageId, uint16_t addr, uint32_t value);
LmnStatus_t EepromMcuReadVariable32(uint8_t pageId, uint16_t addr, uint32_t* value);

#ifdef __cplusplus
}
#endif

#endif // __EEPROM_BOARD_H__
