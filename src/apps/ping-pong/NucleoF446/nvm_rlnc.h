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
    CORRUPT_PRNG_SEED_ZERO = 24,
    CORRUPT_FRAG_SEQ = 25000,
    CORRUPT_FRAG_GEN = 26000,
    CORRUPT_UPDATE_PREFIX = 27000,
    CORRUPT_UPDATE_INDEX = 28000,
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
    IDLE = 0x00,
    PRE_INIT = 0x1,
    IN_GENERATION = 0x3000,
    UPDATING_GENERATION = 0x4000,
    PRE_TERMINATION = 0x5,
    POST_TERMINATION = 0x6
};

// 0x00 is sector header and should only be written to if sector is full
#define SECTOR_HEADER ((uint16_t)0x0000)
#define GEN_PREFIX_HEADER 0xFFFF0000

#define GEN_PREFIX_BYTES 4U
#define UPDATE_PREFIX_BYTES 4U
#define FRAG_META_BYTES 7U // seed(4), gen(1), seq1,seq2

#define SEED_STATE_BYTE 0U
#define SEED_STATE_BYTE1 1U
#define SEED_STATE_BYTE2 2U
#define SEED_STATE_BYTE3 3U
#define GEN_INDEX_BYTE 4U
#define SEQ_BYTE 5U
#define SEQ_BYTE2 6U

#define INIT_SIZE_LIMIT 35U
#define TERM_SIZE_LIMIT 30U
#define FRAG_SIZE_LIMIT 25U
#define FULL_FRAG_SIZE_LIMIT 10000U  // We load all gen fragments in memory

// Startup functionality
uint16_t ValidateRlncFlashState();
uint32_t GetCurrentTimerPeriod();

// Runtime functionality
uint16_t GetRlncFlashState();
uint16_t GetRlncSessionState();
uint16_t StartRlncSessionFromFlash(const RlncRemoteFlashStartCommand& command);
uint16_t StopRlncSessionFromFlash();
void SendLoRaRlncSessionResponse();
bool IsRlncSessionStarted();
bool IsNextTimedActionReady();
uint16_t ProgressRlncSession();

#endif  // NVM_RLNC_H
