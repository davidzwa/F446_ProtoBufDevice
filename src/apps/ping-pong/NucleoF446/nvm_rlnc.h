#ifndef NVM_RLNC_H
#define NVM_RLNC_H

#include <stdint.h>
#include "firmware.h"

enum RlncFlashState {
    UNSCANNED = 0,
    READ_FAIL_SECTOR = 1,
    READ_FAIL_INIT = 11,
    READ_FAIL_TERM = 12,
    READ_FAIL_INIT_BUFFER = 13,
    READ_FAIL_GEN_PREFIX = 14000,
    READ_FAIL_FRAG_META = 15000,
    READ_FAIL_FRAG = 16000,
    READ_FAIL_UPDATE_CMD = 17000,
    CORRUPT_SECTOR = 2,
    CORRUPT_INIT_SIZE = 21,
    CORRUPT_TERM_SIZE = 22,
    CORRUPT_FRAG_SIZE_CONF = 23,
    CORRUPT_LFSR_ZERO = 24,
    CORRUPT_FRAG_SEQ = 25000,
    CORRUPT_FRAG_GEN = 26000,
    CORRUPT_UPDATE_CMD_SIZE = 28000,
    CORRUPT_UPDATE_CMD = 29000,
    DESERIALIZE_FAIL_INIT = 31,
    DESERIALIZE_FAIL_TERM = 32,
    // The generation index get added assuming it falls in range 0-999
    GENERATION_FAIL_PREFIX_BASE = 40000,
    GENERATION_FAIL_FRAG_COUNT_ZERO = 41000,
    GENERATION_FAIL_FRAG_COUNT_EXCEEDS = 42000,
    GENERATION_FULL_FRAG_SIZE_EXCEEDS = 43000,
    GENERATION_FULL_FRAG_SIZE_INCORRECT = 44000,
    VALIDATING = 5,
    VALID = 6
};

enum RlncSessionState {
    IDLE = 0,
    PRE_INIT = 1,
    POST_INIT = 2,
    IN_GENERATION = 30000,
    UPDATING_GENERATION = 40000,
    PRE_TERMINATION = 5,
    POST_TERMINATION = 6
};

// 0x00 is sector header and should only be written to if sector is full
#define SECTOR_HEADER ((uint16_t)0x0000)
#define GEN_PREFIX_HEADER 0xFFFF0000

#define GEN_PREFIX_BYTES 4
#define UPDATE_PREFIX_BYTES 4
#define FRAG_META_BYTES 3

#define LFSR_BYTE 0
#define SEQ_BYTE 1
#define GEN_INDEX_BYTE 2

#define INIT_SIZE_LIMIT 20U
#define TERM_SIZE_LIMIT 30U
#define FRAG_SIZE_LIMIT 25U
#define UPDATE_CMD_SIZE_LIMIT 30U
#define FULL_FRAG_SIZE_LIMIT 10000U  // We load all gen fragments in memory

// Startup functionality
uint16_t GetRlncFlashState();
uint16_t ValidateRlncFlashState();

// Runtime functionality
uint16_t StartRlncSessionFromFlash(RlncRemoteFlashStartCommand& command);
bool IsRlncSessionStarted();
bool IsNextTimedActionReady();
uint16_t ProgressRlncSession();

#endif  // NVM_RLNC_H
