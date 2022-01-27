#ifndef __EEPROM_H
#define __EEPROM_H

#include "stm32f4xx_hal.h"
#include "utilities.h"

/* EEPROM emulation firmware error codes */
#define EE_OK      (uint32_t)HAL_OK
#define EE_ERROR   (uint32_t)HAL_ERROR
#define EE_BUSY    (uint32_t)HAL_BUSY
#define EE_TIMEOUT (uint32_t)HAL_TIMEOUT

/* Define the size of the sectors to be used */
#define PAGE_SIZE               (uint32_t)0x4000  /* Page size = 16KByte */

/* Device voltage range supposed to be [2.7V to 3.6V], the operation will 
   be done by word  */
#define VOLTAGE_RANGE           (uint8_t)VOLTAGE_RANGE_3

/* EEPROM start address in Flash */
// Sector 4 (to ensure 0-3 dont overwrite code) start at 0x08008000
#define EEPROM_START_ADDRESS ((uint32_t)0x08020000)

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x0000))
#define PAGE0_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))
#define PAGE0_ID               FLASH_SECTOR_2

#define PAGE1_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x4000))
#define PAGE1_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (2 * PAGE_SIZE - 1)))
#define PAGE1_ID               FLASH_SECTOR_3

/* No valid page define */
#define NO_VALID_PAGE         ((uint16_t)0x00AB)

/* Page status definitions */
#define ERASED                ((uint16_t)0xFFFF)     /* Page is empty */
#define FILLED_PAGE           ((uint16_t)0xEEEE)     // Page is filled with valuable data (avoid erase)
#define VALID_PAGE            ((uint16_t)0x0000)     /* Page containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE  ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Page errors */
#define PAGE_ILLEGAL_HEADER   ((uint8_t)0x78)
#define PAGE_ILLEGAL_ID       ((uint8_t)0x79) // Page ID is not valid or was not enabled
#define PAGE_FULL             ((uint8_t)0x80)
#define PAGE_OVERRUN          ((uint8_t)0x81) // Address given does not fit in page

/* Exported functions ------------------------------------------------------- */
uint16_t EE_Init(void);
uint16_t EepromMcuReadVariable32(uint16_t virtAddress, uint32_t* data);
uint16_t EepromMcuWriteVariable32(uint16_t virtAddress, uint32_t data);

#endif /* __EEPROM_H */
