#include <math.h>
#include <stdint.h>

#ifndef MEASUREMENTS_H_NVMM__
#define MEASUREMENTS_H_NVMM__

// Also defined in eeprom-conf.h
// Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
// Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
// Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
// Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbytes
// Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
// Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes
// Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbytes
// Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbytes

// 0x00 is sector header and should only be written to if sector is full
#define SECTOR_HEADER               ((uint16_t)0x0000)

// Fields useful for later
#define RESERVED1                   ((uint16_t)0x0001)
#define RESERVED2                   ((uint16_t)0x0002)
#define RESERVED3                   ((uint16_t)0x0003)

#define DATA_SECTOR_BASE            ((uint16_t)0x0004) // in 32-bits
#define DATA_SECTOR_END             ((uint16_t)0x7FFF) // in 32-bits (32k measurements)

uint16_t ClearStorage();
uint32_t GetMeasurementCount();
uint16_t AppendMeasurement(uint32_t value);
uint16_t FlashReadMeasurement(uint32_t index, uint32_t* value);

// 32000 32-bit values in sector
// 1 for header, 2 reserved for future use and 2 for counting (both containing same value for safety checks)
#define MAX_MEASUREMENT_NUM (32000-4)

#define ADDRESS_ALREADY_WRITTEN             ((uint16_t)0xFFFB)
#define ADDRESS_OUT_OF_BOUNDS               ((uint16_t)0xFFFC)
#define CLEAR_ERROR                         ((uint16_t)0xFFFD)
#define WRITE_ERROR                         ((uint16_t)0xFFFE)
#define READ_ERROR                          ((uint16_t)0xFFFF)

#endif // MEASUREMENTS_H_NVMM__
