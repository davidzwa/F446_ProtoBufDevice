/*!
 * \file      eeprom-board.c
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
#include "eeprom-board.h"

#include <stdbool.h>
#include <stdint.h>

#include "eeprom_emul.h"
#include "stm32f4xx.h"
#include "utilities.h"

__IO uint32_t ErasingOnGoing = 0;

/*!
 * \brief Initializes the EEPROM emulation module.
 */
void EepromMcuInit(void) {
    EE_Status eeStatus = EE_OK;

    // Unlock the Flash Program Erase controller
    HAL_FLASH_Unlock();

    // Set EEPROM emulation firmware to erase all potentially incompletely erased
    // pages if the system came from an asynchronous reset. Conditional erase is
    // safe to use if all Flash operations where completed before the system reset
    if (__HAL_PWR_GET_FLAG(PWR_FLAG_SB) == RESET) {
        // System reset comes from a power-on reset: Forced Erase
        // Initialize EEPROM emulation driver (mandatory)
        eeStatus = EE_Init(EepromVirtualAddress, EE_FORCED_ERASE);
        if (eeStatus != EE_OK) {
            assert_param(LMN_STATUS_ERROR);
        }
    } else {
        // Clear the Standby flag
        __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB);

        // Check and Clear the Wakeup flag
        if (__HAL_PWR_GET_FLAG(PWR_FLAG_WU) != RESET) {
            __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        }

        // System reset comes from a STANDBY wakeup: Conditional Erase
        // Initialize EEPROM emulation driver (mandatory)
        eeStatus = EE_Init(EepromVirtualAddress, EE_CONDITIONAL_ERASE);
        if (eeStatus != EE_OK) {
            assert_param(LMN_STATUS_ERROR);
        }
    }

    // Lock the Flash Program Erase controller
    HAL_FLASH_Lock();
}

/*!
 * \brief Indicates if an erasing operation is on going.
 *
 * \retval isEradingOnGoing Returns true is an erasing operation is on going.
 */
bool EepromMcuIsErasingOnGoing(void) {
    return ErasingOnGoing;
}

LmnStatus_t EepromMcuWriteBuffer(uint16_t addr, uint8_t *buffer, uint16_t size) {
    LmnStatus_t status = LMN_STATUS_OK;
    EE_Status eeStatus = EE_OK;

    // Unlock the Flash Program Erase controller
    HAL_FLASH_Unlock();

    CRITICAL_SECTION_BEGIN();
    for (uint32_t i = 0; i < size; i++) {
        eeStatus |= EE_WriteVariable8bits(EepromVirtualAddress[addr + i], buffer[i]);
    }
    CRITICAL_SECTION_END();

    if (eeStatus != EE_OK) {
        status = LMN_STATUS_ERROR;
    }

    if ((eeStatus & EE_STATUSMASK_CLEANUP) == EE_STATUSMASK_CLEANUP) {
        ErasingOnGoing = 0;
        eeStatus |= EE_CleanUp();
    }
    if ((eeStatus & EE_STATUSMASK_ERROR) == EE_STATUSMASK_ERROR) {
        status = LMN_STATUS_ERROR;
    }

    // Lock the Flash Program Erase controller
    HAL_FLASH_Lock();
    return status;
}

LmnStatus_t EepromMcuReadBuffer(uint16_t addr, uint8_t *buffer, uint16_t size) {
    LmnStatus_t status = LMN_STATUS_OK;

    // Unlock the Flash Program Erase controller
    HAL_FLASH_Unlock();

    for (uint32_t i = 0; i < size; i++) {
        if (EE_ReadVariable8bits(EepromVirtualAddress[addr + i], buffer + i) != EE_OK) {
            status = LMN_STATUS_ERROR;
            break;
        }
    }

    // Lock the Flash Program Erase controller
    HAL_FLASH_Lock();
    return status;
}

/*!
 * \brief  FLASH end of operation interrupt callback.
 * \param  ReturnValue: The value saved in this parameter depends on the ongoing procedure
 *                  Mass Erase: Bank number which has been requested to erase
 *                  Page Erase: Page which has been erased
 *                    (if 0xFFFFFFFF, it means that all the selected pages have been erased)
 *                  Program: Address which was selected for data program
 * \retval None
 */
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue) {
    // Call CleanUp callback when all requested pages have been erased
    if (ReturnValue == 0xFFFFFFFF) {
        EE_EndOfCleanup_UserCallback();
    }
}

/*!
 * \brief  Clean Up end of operation interrupt callback.
 * \param  None
 * \retval None
 */
void EE_EndOfCleanup_UserCallback(void) {
    ErasingOnGoing = 0;
}
