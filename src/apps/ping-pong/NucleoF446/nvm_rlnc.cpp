#include "nvm_rlnc.h"

#include "nvmm.h"

// #define DEBUG_THROW
// Flash bank 5
#define NVM_PAGE (7)
NvmHandle NvmRlnc(NVM_PAGE);

// 0x00 is sector header and should only be written to if sector is full
#define SECTOR_HEADER           ((uint16_t)0x0000)

// Fields useful for later
#define ADDR_INIT_SIZE          ((uint16_t)0x0001)
// Size of packets stored for each generation begin
#define ADDR_UPDATE_SIZE        ((uint16_t)0x0002)
// Size of packets stored for each generation's fragments
#define ADDR_FRAG_SIZE          ((uint16_t)0x0003)
// Size of packet stored for termination
#define ADDR_TERM_SIZE          ((uint16_t)0x0004)

#define DATA_SECTOR_BASE        ((uint16_t)0x0004)  // in 32-bits
#define DATA_SECTOR_END         ((uint16_t)0x7FFF)   // in 32-bits (32k767 measurements)


enum RlncFlashState {
    UNSCANNED = 0,
    NODATA = 1,
    DATAPRESENT = 2,
    VALIDATED = 3

};

RlncFlashState state = UNSCANNED;

RlncFlashState InitRlncFlashState() {
}

// Future use
// #define NVM_PAGE2 (7)
// NvmHandle NvmRlnc2(NVM_PAGE2);
