#ifndef NVM_RLNC_H
#define NVM_RLNC_H

// 0x00 is sector header and should only be written to if sector is full
#define SECTOR_HEADER ((uint16_t)0x0000)

// Fields useful for later
#define RESERVED1 ((uint16_t)0x0001)
#define RESERVED2 ((uint16_t)0x0002)
#define RESERVED3 ((uint16_t)0x0003)

#define DATA_SECTOR_BASE ((uint16_t)0x0004)  // in 32-bits
#define DATA_SECTOR_END ((uint16_t)0x7FFF)   // in 32-bits (32k767 measurements)

#endif  // NVM_RLNC_H
