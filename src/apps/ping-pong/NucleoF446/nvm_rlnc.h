#ifndef NVM_RLNC_H
#define NVM_RLNC_H

enum RlncFlashState {
    UNSCANNED = 0,
    READ_FAIL_SECTOR = 1,
    READ_FAIL_INIT = 11,
    READ_FAIL_TERM = 12,
    READ_FAIL_INIT_BUFFER = 13,
    CORRUPT_SECTOR = 2,
    CORRUPT_INIT_SIZE = 21,
    CORRUPT_TERM_SIZE = 22,
    DESERIALIZE_FAIL_INIT = 31,
    DESERIALIZE_FAIL_TERM = 32,
    NODATA = 3,
    DATAPRESENT = 4,
    VALIDATED = 5

};

#define INIT_SIZE_LIMIT 20
#define TERM_SIZE_LIMIT 30

RlncFlashState GetRlncFlashState();
RlncFlashState InitRlncFlashState();

#endif  // NVM_RLNC_H
