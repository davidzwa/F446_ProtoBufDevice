/*!
 * \file      nvmm.h
 *
 * \brief     None volatile memory management module
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
 *               ___ _____ _   ___ _  _____ ___  ___  ___ ___
 *              / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 *              \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 *              |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 *              embedded.connectivity.solutions===============
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 *
 * \author    Daniel Jaeckle ( STACKFORCE )
 *
 * \author    Johannes Bruder ( STACKFORCE )
 */
#ifndef __NVMM_H__
#define __NVMM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "eeprom-board.h"

class NvmHandle {
   public:
    NvmHandle(uint8_t pageId);
    uint16_t Write(uint16_t address, uint32_t variable);

    uint16_t ReadBuffer8(uint32_t address, uint8_t* buffer, size_t length);
    uint16_t Read8(uint32_t address, uint8_t* variable);
    uint16_t Read16(uint32_t address, uint16_t* variable);
    uint16_t Read32(uint32_t address, uint32_t* variable);
    bool Clear();

   private:
    uint8_t pageId;
};

#ifdef __cplusplus
}
#endif

#endif  // __NVMM_H__
