
#include <stdbool.h>

#include "eeprom-conf.h"

uint16_t GetPageHeader(uint8_t pageId);
HAL_StatusTypeDef SetPageHeader(uint8_t pageId, uint32_t header);
HAL_StatusTypeDef EnsurePageErased(uint8_t pageId);
HAL_StatusTypeDef ValidatePageId(uint8_t pageId);
HAL_StatusTypeDef ValidatePageLimits(uint8_t pageId, uint16_t offset);
uint32_t GetPageOffsetAddress(uint8_t pageId, uint16_t offset);

///// PUBLIC FUNCTIONS /////

/**
 * @brief Initialize MCU Init
 *
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef EepromMcuInit(void) {
    HAL_FLASH_Unlock();

    uint16_t pageStatus0 = GetPageHeader(PAGE0_ID);
    if (pageStatus0 != VALID_PAGE) {
        EnsurePageErased(PAGE0_ID);
        SetPageHeader(PAGE0_ID, VALID_PAGE);
    }

    uint16_t pageStatus1 = GetPageHeader(PAGE1_ID);
    if (pageStatus1 != VALID_PAGE) {
        EnsurePageErased(PAGE1_ID);
        SetPageHeader(PAGE1_ID, VALID_PAGE);
    }

    uint16_t pageStatus2 = GetPageHeader(PAGE2_ID);
    if (pageStatus2 != VALID_PAGE) {
        EnsurePageErased(PAGE2_ID);
        SetPageHeader(PAGE2_ID, VALID_PAGE);
    }

    HAL_FLASH_Lock();

    return HAL_OK;
}

HAL_StatusTypeDef EepromMcuClearPage(uint8_t pageId) {
    HAL_FLASH_Unlock();
    HAL_StatusTypeDef result = EnsurePageErased(pageId);
    HAL_FLASH_Lock();
    return result;
}

/**
 * @brief Read 32-bit variable
 *
 * @param pageAddress
 * @param data
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef EepromMcuReadVariable32(uint8_t pageId, uint16_t pageAddress, uint32_t* data) {
    uint32_t dataAddress;
    HAL_StatusTypeDef result = HAL_OK;

    HAL_FLASH_Unlock();

    if (ValidatePageId(pageId) != PAGE_ILLEGAL_ID) {
        result = ValidatePageLimits(pageId, pageAddress);
        if (result == HAL_OK) {
            dataAddress = GetPageOffsetAddress(pageId, pageAddress);
            *data = (*(__IO uint32_t*)(dataAddress));
        }
    } else {
        result = PAGE_ILLEGAL_ID;
    }

    HAL_FLASH_Lock();

    return result;  // (0: variable exist, 1: variable doesn't exist)
}

/**
 * @brief Write a 32-bit variable
 *
 * @param pageAddress32
 * @param data
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef EepromMcuWriteVariable32(uint8_t pageId, uint16_t pageAddress32, uint32_t data) {
    uint16_t writeStatus = 0;

    HAL_FLASH_Unlock();

    uint32_t dataAddress;

    if (ValidatePageId(pageId) == PAGE_ILLEGAL_ID) {
        HAL_FLASH_Lock();
        return PAGE_ILLEGAL_ID;
    }

    if (ValidatePageLimits(pageId, pageAddress32) != HAL_OK) {
        HAL_FLASH_Lock();
        return PAGE_OVERRUN;
    }

    dataAddress = GetPageOffsetAddress(pageId, pageAddress32);
    if (dataAddress == PAGE_ILLEGAL_ID) {
        HAL_FLASH_Lock();
        return PAGE_ILLEGAL_ID;
    }

    CRITICAL_SECTION_BEGIN();

    writeStatus = HAL_FLASH_Program(TYPEPROGRAM_WORD, dataAddress, data);

    CRITICAL_SECTION_END();

    HAL_FLASH_Lock();

    /* Return last operation status */
    return writeStatus;
}

/**
 * @brief Clear all the configured pages in flash
 *
 * @return bool (0: success, 1 failed)
 */
bool ClearAllPages() {
    HAL_FLASH_Unlock();

    uint16_t status1 = EnsurePageErased(PAGE0_ID);
    uint16_t status2 = EnsurePageErased(PAGE1_ID);

    uint16_t status3 = SetPageHeader(PAGE0_ID, VALID_PAGE);

    HAL_FLASH_Lock();

    // HAL_OK=0x00 if all good - otherwise 0x01
    return !(status1 == HAL_OK && status2 == HAL_OK && status3 == HAL_OK);
}

///// PRIVATE FUNCTIONS /////

HAL_StatusTypeDef ValidatePageId(uint8_t pageId) {
    if (pageId != PAGE2_ID && pageId != PAGE1_ID && pageId != PAGE0_ID) {
        return PAGE_ILLEGAL_ID;
    }

    return HAL_OK;
}

uint32_t GetPageBaseAddress(uint8_t pageId) {
    if (pageId == PAGE0_ID) {
        return PAGE0_BASE_ADDRESS;
    } else if (pageId == PAGE1_ID) {
        return PAGE1_BASE_ADDRESS;
    } else if (pageId == PAGE2_ID) {
        return PAGE2_BASE_ADDRESS;
    } else {
        return PAGE_ILLEGAL_ID;
    }
}

uint32_t GetPageEndAddress(uint8_t pageId) {
    if (pageId == PAGE0_ID) {
        return PAGE0_END_ADDRESS;
    } else if (pageId == PAGE1_ID) {
        return PAGE1_END_ADDRESS;
    } else if (pageId == PAGE2_ID) {
        return PAGE2_END_ADDRESS;
    } else {
        return PAGE_ILLEGAL_ID;
    }
}

uint32_t GetPageOffsetAddress(uint8_t pageId, uint16_t offset) {
    uint32_t pageBaseAddress = GetPageBaseAddress(pageId);
    if (pageBaseAddress == PAGE_ILLEGAL_ID) return PAGE_ILLEGAL_ID;

    return pageBaseAddress + offset;
}

HAL_StatusTypeDef ValidatePageLimits(uint8_t pageId, uint16_t offset) {
    uint32_t baseAddress = GetPageBaseAddress(pageId);
    uint32_t endAddress = GetPageEndAddress(pageId);
    if (baseAddress == PAGE_ILLEGAL_ID || endAddress == PAGE_ILLEGAL_ID) {
        return PAGE_ILLEGAL_ID;
    }

    if (baseAddress + offset > endAddress) return PAGE_OVERRUN;

    return HAL_OK;
}

uint16_t GetPageHeader(uint8_t pageId) {
    if (ValidatePageId(pageId) != HAL_OK) {
        return PAGE_ILLEGAL_ID;
    }

    uint32_t pageBaseAddress = GetPageBaseAddress(pageId);

    // Requires flash to be unlocked
    return (*(__IO uint16_t*)pageBaseAddress);
}

HAL_StatusTypeDef SetPageHeader(uint8_t pageId, uint32_t header) {
    if (ValidatePageId(pageId) != HAL_OK) {
        return PAGE_ILLEGAL_ID;
    }

    if (header != VALID_PAGE && header != ERASED_PAGE) {
        return PAGE_ILLEGAL_HEADER;
    }

    uint32_t pageBaseAddress = GetPageBaseAddress(pageId);
    return HAL_FLASH_Program(TYPEPROGRAM_HALFWORD, pageBaseAddress, header);
}

HAL_StatusTypeDef EnsurePageErased(uint8_t pageId) {
    FLASH_EraseInitTypeDef pageEraseInit;
    HAL_StatusTypeDef flashStatus;
    uint32_t sectorError = 0, address = 0;
    bool pageDirty = false;
    uint16_t addressValue;

    HAL_StatusTypeDef validation = ValidatePageId(pageId);
    if (validation == PAGE_ILLEGAL_ID) {
        return PAGE_ILLEGAL_ID;
    }

    // We dont check page-id validity again
    uint32_t pageEndAddress = GetPageEndAddress(pageId);
    address = GetPageBaseAddress(pageId);
    pageEraseInit.Sector = pageId;
    pageEraseInit.NbSectors = 1;
    pageEraseInit.VoltageRange = VOLTAGE_RANGE;

    /* Check value 0xFFFFFFFF - requires flash to be unlocked */
    while (address <= pageEndAddress) {
        addressValue = (*(__IO uint16_t*)address);

        if (addressValue != ERASED_PAGE) {
            pageDirty = true;
            break;
        }

        address = address + 4;
    }

    // Erase - requires flash to be unlocked
    if (pageDirty) {
        flashStatus = HAL_FLASHEx_Erase(&pageEraseInit, &sectorError);

        if (flashStatus != HAL_OK) {
            return flashStatus;
        }
    }

    return HAL_OK;
}
