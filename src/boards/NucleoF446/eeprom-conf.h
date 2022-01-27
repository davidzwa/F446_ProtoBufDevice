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
#define PAGE_SIZE_16K          (uint32_t)0x4000  /* Page size = 16KByte */
#define PAGE_SIZE_64K          (uint32_t)0x10000 /* Page size = 64KByte */
#define PAGE_SIZE_128K         (uint32_t)0x20000 /* Page size = 128KByte */

// Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
#define SECTOR0_START           0x08000000
// Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
#define SECTOR1_START           0x08004000
// Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
#define SECTOR2_START           0x08008000
// Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbytes
#define SECTOR3_START           0x0800C000
// Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
#define SECTOR4_START           0x08010000
// Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes
#define SECTOR5_START           0x08020000
// Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbytes
#define SECTOR6_START           0x08040000
// Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbytes
#define SECTOR7_START           0x08060000

/* Device voltage range supposed to be [2.7V to 3.6V], the operation will 
   be done by word  */
#define VOLTAGE_RANGE           (uint8_t)VOLTAGE_RANGE_3

/* EEPROM start address in Flash */
// Sector 4 (to ensure 0-3 dont overwrite code) start at 0x08008000
#define EEPROM_START_ADDRESS ((uint32_t)0x08000000)

/* Pages 0 and 1 base and end addresses */
#define PAGE0_ID              FLASH_SECTOR_5
#define PAGE0_SIZE            PAGE_SIZE_128K
#define PAGE0_BASE_ADDRESS    ((uint32_t)(SECTOR5_START))
#define PAGE0_END_ADDRESS     ((uint32_t)(SECTOR5_START + (PAGE0_SIZE - 1)))

#define PAGE1_ID              FLASH_SECTOR_6
#define PAGE1_SIZE            PAGE_SIZE_128K
#define PAGE1_BASE_ADDRESS    ((uint32_t)(SECTOR6_START))
#define PAGE1_END_ADDRESS     ((uint32_t)(SECTOR6_START + (PAGE1_SIZE - 1)))

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
