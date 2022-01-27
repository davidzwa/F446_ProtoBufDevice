#include <math.h>
#include <stdint.h>

#ifndef MEASUREMENTS_H_NVVM__
#define MEASUREMENTS_H_NVVM__

// Also defined in eeprom-conf.h
// Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
// Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
// Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
// Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbytes
// Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
// Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes
// Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbytes
// Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbytes

// 0x00 is page header and should only be written to if sector is full
#define MEASUREMENT_COUNTER         ((uint16_t)0x0000)

// Application header fields
#define MEASUREMENT_COUNTER         ((uint16_t)0x0001)
#define MEASUREMENT_COUNTER_BACKUP  ((uint16_t)0x0002)
// Fields useful for later
#define RESERVED1                   ((uint16_t)0x0003)
#define RESERVED2                   ((uint16_t)0x0004)
#define RESERVED3                   ((uint16_t)0x0005)
#define RESERVED4                   ((uint16_t)0x0006) 

#define DATA_SECTOR_BASE            ((uint16_t)0x0005)
#define DATA_SECTOR_END             ((uint16_t)0x4000)

#endif // MEASUREMENTS_H_NVVM__
