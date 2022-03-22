#ifndef NVM_RLNC_H
#define NVM_RLNC_H

#include <stdint.h>

enum RlncFlashState {
    UNSCANNED = 0,
    READ_FAIL_SECTOR = 1,
    READ_FAIL_INIT = 11,
    READ_FAIL_TERM = 12,
    READ_FAIL_INIT_BUFFER = 13,
    READ_FAIL_GEN_PREFIX = 14000,
    CORRUPT_SECTOR = 2,
    CORRUPT_INIT_SIZE = 21,
    CORRUPT_TERM_SIZE = 22,
    DESERIALIZE_FAIL_INIT = 31,
    DESERIALIZE_FAIL_TERM = 32,
    // The generation index get added assuming it falls in range 0-999
    GENERATION_FAIL_PREFIX_BASE = 4000,
    NODATA = 3,
    DATAPRESENT = 4,
    VALIDATED = 5

};

#define INIT_SIZE_LIMIT 20
#define TERM_SIZE_LIMIT 30

uint16_t GetRlncFlashState();
uint16_t InitRlncFlashState();

#endif  // NVM_RLNC_H
