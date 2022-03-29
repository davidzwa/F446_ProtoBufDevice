#include "nvm_rlnc.h"

#include <math.h>

#include <vector>

#include "ProtoReadBuffer.h"
#include "cli.h"
#include "config.h"
#include "lora_device_messages.h"
#include "nvmm.h"
#include "radio_config.h"
#include "radio_phy.h"
#include "timer.h"

using namespace std;

// #define DEBUG_THROW
// Flash bank 5
#define NVM_PAGE (7)
NvmHandle NvmRlnc(NVM_PAGE);

void TimerDelayAsync();
static uint16_t LoadCurrentFragment(uint32_t fragmentIndex, uint32_t generationIndex);
static void PrepareNewUpdateCommand(uint32_t nextGenerationIndex);
static uint32_t CalculateGenerationBaseFrameCount(uint32_t generationIndex);
static uint32_t CalculateGenerationTotalFrameCount(uint32_t generationIndex);
static uint32_t CalculateGenerationAddress(uint32_t generationIndex);
static uint32_t CalculateFragmentAddress(uint32_t fragmentIndex, uint32_t generationIndex);
static uint32_t GetRedundancy();
static uint32_t GetFrameSize();
static uint32_t GetGenerationCount();
static const RlncInitConfigCommand& GetConfig();

vector<uint32_t> generationStartAddresses;
uint32_t generationStartAddress8 = 0;
uint32_t initSize8 = 0;
uint32_t termSize8 = 0;

ProtoReadBuffer flashReadBuffer;
LoRaMessage<MAX_LORA_BYTES> initCommand;         // Fixed command
LoRaMessage<MAX_LORA_BYTES> terminationCommand;  // Fixed command
LoRaMessage<MAX_LORA_BYTES> currentFragment;     // Iterated buffer command
LoRaMessage<MAX_LORA_BYTES> updateCommand;       // Iterated buffer command
// Response message
LoRaMessage<MAX_LORA_BYTES> stateResponse;

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

#define TIMER_DELAY_MIN (uint32_t)100

// The serialized Rlnc Init Configuration (Proto, bytes)
#define ADDR_INIT_SIZE ((uint16_t)0x0001)
// Size of packet stored for termination (Proto, bytes)
#define ADDR_TERM_SIZE ((uint16_t)0x0002)
#define DATA_SECTOR_BASE ((uint16_t)0x0003)  // in 32-bits
#define INIT_START8 DATA_SECTOR_BASE * 4     // in 8-bits
#define DATA_SECTOR_END ((uint16_t)0x7FFF)   // in 32-bits (32k767 measurements)

bool nextActionReady = false;
uint32_t currentGenerationIndex = 0;
uint32_t currentFragmentIndex = 0;
uint32_t currentTimerPeriod = 0;
uint32_t currentDeviceId0 = 0;
bool currentSetIsMulticast = false;
uint16_t state = RlncFlashState::UNSCANNED;
uint16_t sessionState = RlncSessionState::IDLE;

bool IsNextTimedActionReady() {
    return nextActionReady;
}

bool IsRlncSessionStarted() {
    return sessionState != RlncSessionState::IDLE;
}

uint16_t StartRlncSessionFromFlash(const RlncRemoteFlashStartCommand& command) {
    if (state != RlncFlashState::VALID) return state;

    SetTxConfig(command.get_transmitConfiguration());

    sessionState = RlncSessionState::PRE_INIT;
    currentFragmentIndex = 0;
    currentGenerationIndex = 0;

    // TODO apply below
    currentDeviceId0 = command.get_DeviceId0();
    // TODO apply below
    currentSetIsMulticast = command.get_SetIsMulticast();
    currentTimerPeriod = command.get_TimerDelay();
    UartDebug("RLNC", 0, 4);
    TimerDelayAsync();
    return 0x00;
}

uint16_t StopRlncSessionFromFlash() {
    TimerStop(&rlncDelayTimer);
    UartDebug("RLNC", 0xFF, 4);

    return sessionState = RlncSessionState::PRE_TERMINATION;
}

uint16_t ProgressRlncSession() {
    nextActionReady = false;

    auto generationCount = GetGenerationCount();
    if (sessionState == RlncSessionState::PRE_INIT) {
        TransmitLoRaMessage(initCommand);
        UartDebug("RLNC", 2, 4);
        sessionState = RlncSessionState::IN_GENERATION;
    } else if (sessionState == RlncSessionState::IN_GENERATION) {
        // TODO validate fragment makes sense
        LoadCurrentFragment(currentFragmentIndex, currentGenerationIndex);

        // Transmit fragment
        TransmitLoRaMessage(currentFragment);
        UartDebug("RLNC", 3, 4);

        // Check if done with generation and not in last generation
        auto generationTotalFragments = CalculateGenerationTotalFrameCount(currentGenerationIndex);
        if (currentFragmentIndex + 1 >= generationTotalFragments) {
            if (currentGenerationIndex + 1 < generationCount) {
                sessionState = RlncSessionState::UPDATING_GENERATION;
            } else {
                sessionState = RlncSessionState::PRE_TERMINATION;
            }
        }
        else {
            currentFragmentIndex++;
            sessionState = RlncSessionState::IN_GENERATION;
        }
    } else if (sessionState == RlncSessionState::UPDATING_GENERATION) {
        currentGenerationIndex++;
        currentFragmentIndex = 0;
        PrepareNewUpdateCommand(currentGenerationIndex);
        TransmitLoRaMessage(updateCommand);
        sessionState = RlncSessionState::IN_GENERATION;
        UartDebug("RLNC", 4, 4);
    } else if (sessionState == RlncSessionState::PRE_TERMINATION) {
        TransmitLoRaMessage(terminationCommand);
        sessionState = RlncSessionState::POST_TERMINATION;
        UartDebug("RLNC", 0xFE, 4);
    } else if (sessionState == RlncSessionState::POST_TERMINATION) {
        sessionState = RlncSessionState::IDLE;
    }

    if (sessionState != RlncSessionState::IDLE) {
        TimerStart(&rlncDelayTimer);
    }

    return 0x00;
}

uint16_t GetRlncFlashState() {
    return state;
}

uint16_t GetRlncSessionState() {
    return sessionState;
}

uint32_t GetCurrentTimerPeriod() {
    return max(TIMER_DELAY_MIN, currentTimerPeriod);
}

void SendLoRaRlncSessionResponse() {
    stateResponse.clear();
    RlncRemoteFlashResponse response;

    response.set_RlncFlashState(state);
    response.set_RlncSessionState(sessionState);

    response.set_CurrentDeviceId0(currentDeviceId0);
    response.set_CurrentSetIsMulticast(currentSetIsMulticast);
    response.set_CurrentTimerDelay(GetCurrentTimerPeriod());

    response.set_CurrentTxPower(GetTxPower());
    response.set_CurrentTxBandwidth(GetTxBandwidth());
    response.set_CurrentTxDataRate(GetTxDataRate());

    stateResponse.set_rlncRemoteFlashResponse(response);
    stateResponse.set_IsMulticast(false);
    stateResponse.set_DeviceId(NETWORK_RESPONSE_ID);
    TransmitLoRaMessage(stateResponse);
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
    TimerSetValue(&rlncDelayTimer, GetCurrentTimerPeriod());
    TimerStart(&rlncDelayTimer);
}

uint16_t ValidateRlncFlashState() {
    uint32_t pageHeader;
    auto readStatus = NvmRlnc.Read32(SECTOR_HEADER, &pageHeader);
    if (readStatus != 0x00) {
        return state = READ_FAIL_SECTOR;
    }
    if (pageHeader != 0xFFFF0000) {
        return state = CORRUPT_SECTOR;
    }

    // We set the state to unknown but correct state
    state = VALIDATING;

    // Update initSize8 (init command size)
    readStatus = NvmRlnc.Read32(ADDR_INIT_SIZE, &initSize8);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT;
    }
    if (initSize8 > INIT_SIZE_LIMIT) {
        return state = CORRUPT_INIT_SIZE;
    }
    // Update termSize8 (termination command size)
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
    readStatus = NvmRlnc.ReadBuffer8(INIT_START8 + initSize8, bufferTerm, termSize8);
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
    auto initConfig = GetConfig();
    auto generationCount = GetGenerationCount();
    generationStartAddresses.clear();
    auto generationSize = initConfig.get_GenerationSize();
    auto generationRedundancySize = initConfig.get_GenerationRedundancySize();
    uint16_t maxGenerationSize = (uint16_t)generationSize + (uint16_t)generationRedundancySize;
    auto frameSize = GetFrameSize();
    if ((uint8_t)frameSize > FRAG_SIZE_LIMIT) {
        return state = CORRUPT_FRAG_SIZE_CONF;
    }

    // Update the 8-bit address where repeated data starts
    generationStartAddress8 = INIT_START8 + initSize8 + termSize8;
    auto currentAddress8 = generationStartAddress8;

    uint8_t currentGenerationPrefix[GEN_PREFIX_BYTES];
    uint8_t currentUpdateCmdPrefix[UPDATE_PREFIX_BYTES];
    uint16_t currentGenerationSize = 0;
    uint8_t currentFragmentMeta[FRAG_META_BYTES];
    uint8_t currentFragment[(size_t)frameSize];
    uint32_t currentSequenceNumber = 0;
    uint16_t result;
    for (size_t i = 0; i < generationCount; i++) {
        // Update the generation size - only important for the last generation with possibly less fragments
        currentGenerationSize = CalculateGenerationTotalFrameCount(i);
        if (currentGenerationSize == 0) {
            return state = GENERATION_FAIL_FRAG_COUNT_ZERO + i;
        }
        if (currentGenerationSize > maxGenerationSize) {
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
        auto fullFragmentSize = (frameSize + FRAG_META_BYTES) * currentGenerationSize;
        if (genFragmentSizeBytes != fullFragmentSize) {
            return state = GENERATION_FULL_FRAG_SIZE_INCORRECT + i;
        }

        // Advance beyond generation prefix
        generationStartAddresses.push_back(currentAddress8);
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
            result = NvmRlnc.ReadBuffer8(currentAddress8, currentFragment, frameSize);
            if (result != 0x00) {
                return state = READ_FAIL_FRAG + currentSequenceNumber;
            }

            // Advance beyond fragment bytes
            currentAddress8 += frameSize;

            currentSequenceNumber++;
        }

        // Parse and deserialize the update command between each generation
        if (i + 1 < generationCount) {
            result = NvmRlnc.ReadBuffer8(currentAddress8, currentUpdateCmdPrefix, UPDATE_PREFIX_BYTES);
            if (result != 0x00) {
                return state = READ_FAIL_UPDATE_CMD + currentSequenceNumber;
            }
            if (currentUpdateCmdPrefix[0] != 0xFF || currentUpdateCmdPrefix[1] != 0xFF) {
                return state = CORRUPT_UPDATE_PREFIX + i + 1;
            }

            uint16_t nextGenerationIndex = (((uint16_t)currentUpdateCmdPrefix[2]) << 8) | (uint16_t)currentUpdateCmdPrefix[3];
            if (nextGenerationIndex != i + 1) {
                return state = CORRUPT_UPDATE_INDEX + i + 1;
            }

            currentAddress8 += UPDATE_PREFIX_BYTES;
        }
    }

    return state = VALID;
}

static uint16_t LoadCurrentFragment(uint32_t fragmentIndex, uint32_t generationIndex) {
    auto fragmentAddress = CalculateFragmentAddress(fragmentIndex, generationIndex);
    uint32_t frameSize = GetFrameSize();
    uint8_t fragmentMetaBuffer[FRAG_META_BYTES];
    uint8_t fragmentBuffer[frameSize];

    // Read frag metadata
    auto result = NvmRlnc.ReadBuffer8(fragmentAddress, fragmentMetaBuffer, FRAG_META_BYTES);
    if (result != 0x00) {
        return state = READ_FAIL_FRAG_META + fragmentIndex;
    }

    // Read frag - what can we validate except for accessibility?
    result = NvmRlnc.ReadBuffer8(fragmentAddress + FRAG_META_BYTES, fragmentBuffer, frameSize);
    if (result != 0x00) {
        return state = READ_FAIL_FRAG + fragmentIndex;
    }

    RlncEncodedFragment fragment;
    fragment.set_LfsrState(fragmentMetaBuffer[LFSR_BYTE]);

    currentFragment.clear();
    currentFragment.set_rlncEncodedFragment(fragment);
    currentFragment.mutable_Payload().set(fragmentBuffer, frameSize);

    return 0x00;
}

static void PrepareNewUpdateCommand(uint32_t nextGenerationIndex) {
    updateCommand.mutable_rlncStateUpdate().set_GenerationIndex(nextGenerationIndex);
}

static uint32_t CalculateGenerationAddress(uint32_t generationIndex) {
    return generationStartAddresses[generationIndex];
}

static uint32_t CalculateFragmentAddress(uint32_t fragmentIndex, uint32_t generationIndex) {
    auto generationAddress8 = CalculateGenerationAddress(generationIndex);
    return generationAddress8 + GEN_PREFIX_BYTES + fragmentIndex * (GetFrameSize() + FRAG_META_BYTES);
}

/**
 * @brief Get the Generation Frame count left-over based on config and generation index
 *
 * @param generationIndex
 * @return uint32_t
 */
static uint32_t CalculateGenerationBaseFrameCount(uint32_t generationIndex) {
    auto config = GetConfig();
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

static uint32_t CalculateGenerationTotalFrameCount(uint32_t generationIndex) {
    auto config = GetConfig();
    return CalculateGenerationBaseFrameCount(generationIndex) + GetRedundancy();
}

static uint32_t GetRedundancy() {
    return GetConfig().get_GenerationRedundancySize();
}

static uint32_t GetFrameSize() {
    return GetConfig().get_FrameSize();
}

static uint32_t GetGenerationCount() {
    return GetConfig().get_GenerationCount();
}

static const RlncInitConfigCommand& GetConfig() {
    return initCommand.get_rlncInitConfigCommand();
}

static void DebugRlncCode(uint32_t code) {

}