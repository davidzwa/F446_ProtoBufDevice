#include "nvm_rlnc.h"

#include "ProtoReadBuffer.h"
#include "config.h"
#include "lora_device_messages.h"
#include "nvmm.h"
#include "radio_phy.h"
#include "radio_config.h"
#include "timer.h"

// #define DEBUG_THROW
// Flash bank 5
#define NVM_PAGE (7)
NvmHandle NvmRlnc(NVM_PAGE);

static uint32_t GetGenerationFrameCount(RlncInitConfigCommand& config, uint32_t generationIndex);
void TimerDelayAsync();
RlncInitConfigCommand GetConfig();
uint32_t GetGenerationCount();

ProtoReadBuffer flashReadBuffer;
LoRaMessage<MAX_LORA_BYTES> initCommand;       // Fixed command
LoRaMessage<MAX_LORA_BYTES> terminationCommand;  // Fixed command
LoRaMessage<MAX_LORA_BYTES> currentFragment;   // Iterated buffer command
LoRaMessage<MAX_LORA_BYTES> updateCommand;     // Iterated buffer command

static TimerEvent_t rlncDelayTimer;

// LAYOUT
// -- Start of header --
// --> Page header (32 bits)
// --> Init Size Header (32 bits)
// --> Termination Size Header (32 bits)
// -- End of header --
// --> Packet Rlnc Init (fixed size)
// --> Packet Rlnc Termination (fixed size)
// for each g in generations
//      -- SYNC HEADER 0xFFFF + Length (16+16 bits) --
//      for all packets in generation
//          --> RAW meta + fragment
//      -- SYNC HEADER 0xFFFF + Update Length (16+16 bits) --
//      --> Packet Rlnc Update (unless g index is 0)

#define TIMER_DELAY 500
bool nextActionReady = false;
uint32_t currentGenerationIndex = 0;
uint32_t currentFragmentIndex = 0;

// The serialized Rlnc Init Configuration (Proto, bytes)
#define ADDR_INIT_SIZE ((uint16_t)0x0001)
// Size of packet stored for termination (Proto, bytes)
#define ADDR_TERM_SIZE ((uint16_t)0x0002)

#define DATA_SECTOR_BASE ((uint16_t)0x0003)  // in 32-bits
#define INIT_START8 DATA_SECTOR_BASE * 4     // in 8-bits
#define DATA_SECTOR_END ((uint16_t)0x7FFF)   // in 32-bits (32k767 measurements)

uint16_t state = RlncFlashState::UNSCANNED;
uint16_t sessionState = RlncSessionState::IDLE;

bool IsNextTimedActionReady() {
    return nextActionReady;
}

bool IsRlncSessionStarted() {
    return sessionState != RlncSessionState::IDLE;
}

uint16_t StartRlncSessionFromFlash(RlncRemoteFlashStartCommand& command) {
    if (state != RlncFlashState::VALID) return state;

    SetTxConfig(command.get_transmitConfiguration());

    state = RlncSessionState::PRE_INIT;
    currentFragmentIndex = 0;
    currentGenerationIndex = 0;
    TimerDelayAsync();
    return 0x00;
}

uint16_t ProgressRlncSession() {
    if (state == RlncSessionState::PRE_INIT) {
        TransmitLoRaMessage(initCommand);
        state = RlncSessionState::POST_INIT;
    } else if (state == RlncSessionState::POST_INIT) {
        state = RlncSessionState::IN_GENERATION;
        // TODO
    } else if (state == RlncSessionState::IN_GENERATION) {
        // TODO load fragment

        // Transmit fragment
        TransmitLoRaMessage(currentFragment);
        currentFragmentIndex++;
        
        // TODO if at end of generation but not last generation
        return state = RlncSessionState::UPDATING_GENERATION;

        // state == RlncSessionState::IN_GENERATION;
        // TODO if done
        auto generationCount = GetGenerationCount();

        state = RlncSessionState::PRE_TERMINATION;
    } else if (state == RlncSessionState::UPDATING_GENERATION) {
        currentGenerationIndex++;

        updateCommand.mutable_rlncStateUpdate().set_GenerationIndex(currentGenerationIndex);
        TransmitLoRaMessage(updateCommand);
        
        state = RlncSessionState::IN_GENERATION;
    }
    else if (state == RlncSessionState::PRE_TERMINATION) {
        TransmitLoRaMessage(terminationCommand);
        state = RlncSessionState::POST_TERMINATION;
    } else if (state == RlncSessionState::POST_TERMINATION) {
        state = RlncSessionState::IDLE;
    }

    return 0x00;
}

uint16_t GetRlncFlashState() {
    return state;
}

/**
 *  Internal functionality below
 *
 * */
static void OnRlncDelayTimerEvent(void* context) {
    nextActionReady = true;
}

void TimerDelayAsync() {
    nextActionReady = false;
    TimerInit(&rlncDelayTimer, OnRlncDelayTimerEvent);
    TimerSetValue(&rlncDelayTimer, TIMER_DELAY);
    TimerStart(&rlncDelayTimer);
}

uint16_t ValidateRlncFlashState() {
    uint32_t pageHeader, initSize8, termSize8;
    auto readStatus = NvmRlnc.Read32(SECTOR_HEADER, &pageHeader);
    if (readStatus != 0x00) {
        return state = READ_FAIL_SECTOR;
    }
    if (pageHeader != 0xFFFF0000) {
        return state = CORRUPT_SECTOR;
    }

    // We set the state to unknown but correct state
    state = VALIDATING;

    readStatus = NvmRlnc.Read32(ADDR_INIT_SIZE, &initSize8);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT;
    }
    if (initSize8 > INIT_SIZE_LIMIT) {
        return state = CORRUPT_INIT_SIZE;
    }
    readStatus = NvmRlnc.Read32(ADDR_TERM_SIZE, &termSize8);
    if (readStatus != 0x00) {
        return state = READ_FAIL_TERM;
    }
    if (termSize8 > TERM_SIZE_LIMIT) {
        return state = CORRUPT_INIT_SIZE;
    }

    // Read and deserialize Initiation command
    uint8_t buffer[initSize8];
    readStatus = NvmRlnc.ReadBuffer8(INIT_START8, buffer, initSize8);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT_BUFFER;
    }
    flashReadBuffer.clear();
    for (size_t i = 0; i < initSize8; i++) {
        flashReadBuffer.push(buffer[i]);
    }
    auto protoErr = initCommand.deserialize(flashReadBuffer);
    if (protoErr != EmbeddedProto::Error::NO_ERRORS) {
        return DESERIALIZE_FAIL_INIT;
    }

    // Read and deserialize Termination command
    uint8_t bufferTerm[termSize8];
    readStatus = NvmRlnc.ReadBuffer8(INIT_START8, bufferTerm, termSize8);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT_BUFFER;
    }
    flashReadBuffer.clear();
    for (size_t i = 0; i < termSize8; i++) {
        flashReadBuffer.push(bufferTerm[i]);
    }
    protoErr = terminationCommand.deserialize(flashReadBuffer);
    if (protoErr != EmbeddedProto::Error::NO_ERRORS) {
        return state = DESERIALIZE_FAIL_TERM;
    }

    // Get generation count from init command
    auto innerInitCommand = GetConfig();
    auto generationCount = GetGenerationCount();
    auto generationSize = innerInitCommand.get_GenerationSize();
    auto generationRedundancySize = innerInitCommand.get_GenerationRedundancySize();
    uint16_t totalGenerationSize = (uint16_t)generationSize + (uint16_t)generationRedundancySize;
    auto fragmentSize = innerInitCommand.get_FrameSize();
    if ((uint8_t)fragmentSize > FRAG_SIZE_LIMIT) {
        return state = CORRUPT_FRAG_SIZE_CONF;
    }

    auto currentAddress8 = INIT_START8 + initSize8 + termSize8;
    uint8_t currentGenerationPrefix[GEN_PREFIX_BYTES];
    uint8_t currentUpdateCmdPrefix[UPDATE_PREFIX_BYTES];
    uint16_t currentGenerationSize = 0;
    uint8_t currentFragmentMeta[FRAG_META_BYTES];
    uint8_t currentFragment[(size_t)fragmentSize];
    uint32_t currentSequenceNumber = 0;
    uint16_t result;
    for (size_t i = 0; i < generationCount; i++) {
        // Update the generation size - only important for the last generation with possibly less fragments
        currentGenerationSize = GetGenerationFrameCount(innerInitCommand, i) + generationRedundancySize;
        if (currentGenerationSize == 0) {
            return state = GENERATION_FAIL_FRAG_COUNT_ZERO + i;
        }
        if (currentGenerationSize > totalGenerationSize) {
            return state = GENERATION_FAIL_FRAG_COUNT_EXCEEDS + i;
        }

        result = NvmRlnc.ReadBuffer8(currentAddress8, currentGenerationPrefix, 4);
        if (result != 0x00) {
            return state = READ_FAIL_GEN_PREFIX + i;
        }

        if (currentGenerationPrefix[0] != 0xFF || currentGenerationPrefix[1] != 0xFF) {
            return state = GENERATION_FAIL_PREFIX_BASE + i;
        }

        uint16_t genFragmentSizeBytes = ((uint16_t)currentGenerationPrefix[2] << 8) + currentGenerationPrefix[3];
        if (genFragmentSizeBytes >= FULL_FRAG_SIZE_LIMIT) {
            return state = GENERATION_FULL_FRAG_SIZE_EXCEEDS + i;
        }
        auto fullFragmentSize = (fragmentSize + FRAG_META_BYTES) * currentGenerationSize;
        if (genFragmentSizeBytes != fullFragmentSize) {
            return state = GENERATION_FULL_FRAG_SIZE_INCORRECT + i;
        }

        // Advance beyond generation prefix
        currentAddress8 += GEN_PREFIX_BYTES;

        for (size_t j = 0; j < currentGenerationSize; j++) {
            // Read frag metadata
            result = NvmRlnc.ReadBuffer8(currentAddress8, currentFragmentMeta, FRAG_META_BYTES);
            if (result != 0x00) {
                return state = READ_FAIL_FRAG_META + currentSequenceNumber;
            }

            // Validate LFSR state not ever to be zero
            if (currentFragmentMeta[LFSR_BYTE] == 0x00) {
                return state = CORRUPT_LFSR_ZERO;
            }
            if (currentFragmentMeta[SEQ_BYTE] != currentSequenceNumber) {
                return state = CORRUPT_FRAG_SEQ + currentSequenceNumber;
            }
            if (currentFragmentMeta[GEN_INDEX_BYTE] != i) {
                return state = CORRUPT_FRAG_GEN + currentSequenceNumber;
            }

            // Advance beyond meta bytes (3)
            currentAddress8 += FRAG_META_BYTES;

            // Read frag - what can we validate except for accessibility?
            result = NvmRlnc.ReadBuffer8(currentAddress8, currentFragment, fragmentSize);
            if (result != 0x00) {
                return state = READ_FAIL_FRAG + currentSequenceNumber;
            }

            // Advance beyond fragment bytes
            currentAddress8 += fragmentSize;

            currentSequenceNumber++;
        }

        // Parse and deserialize the update command between each generation
        if (i + 1 < generationCount) {
            result = NvmRlnc.ReadBuffer8(currentAddress8, currentUpdateCmdPrefix, UPDATE_PREFIX_BYTES);
            if (result != 0x00) {
                return state = READ_FAIL_UPDATE_CMD + currentSequenceNumber;
            }
            if (currentUpdateCmdPrefix[0] != 0xFF || currentUpdateCmdPrefix[1] != 0xFF) {
                return state = CORRUPT_UPDATE_CMD + currentSequenceNumber;
            }

            uint16_t fullFragmentSizeBytes = ((uint16_t)currentUpdateCmdPrefix[2] << 8) + currentUpdateCmdPrefix[3];
            if (fullFragmentSizeBytes >= UPDATE_CMD_SIZE_LIMIT) {
                return state = CORRUPT_UPDATE_CMD_SIZE + currentSequenceNumber;
            }

            currentAddress8 += UPDATE_PREFIX_BYTES;
        }
    }

    return state = VALID;
}

RlncInitConfigCommand GetConfig() {
    return initCommand.get_rlncInitConfigCommand();
}

uint32_t GetGenerationCount() {
    return GetConfig().get_GenerationCount();
}

/**
 * @brief Get the Generation Frame count left-over based on config and generation index
 *
 * @param config
 * @param generationIndex
 * @return uint32_t
 */
static uint32_t GetGenerationFrameCount(RlncInitConfigCommand& config, uint32_t generationIndex) {
    auto generationSize = config.get_GenerationSize();
    auto processedFrames = (generationIndex * generationSize);
    auto totalFrameCountLeft = config.get_TotalFrameCount() - processedFrames;

    // If the total frame count left-over is less than the generation size, we take that
    if (generationSize <= totalFrameCountLeft) {
        return generationSize;
    } else {
        return totalFrameCountLeft;
    }
}