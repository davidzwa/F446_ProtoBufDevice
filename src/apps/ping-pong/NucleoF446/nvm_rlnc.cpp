#include "nvm_rlnc.h"

#include "ProtoReadBuffer.h"
#include "lora_device_messages.h"
#include "nvmm.h"
#include "config.h"

// #define DEBUG_THROW
// Flash bank 5
#define NVM_PAGE (7)
NvmHandle NvmRlnc(NVM_PAGE);

// 0x00 is sector header and should only be written to if sector is full
#define SECTOR_HEADER ((uint16_t)0x0000)

ProtoReadBuffer flashReadBuffer;
LoRaMessage<MAX_LORA_BYTES> initCommand;
LoRaMessage<MAX_LORA_BYTES> terminateCommand;

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

// The serialized Rlnc Init Configuration (Proto, bytes)
#define ADDR_INIT_SIZE ((uint16_t)0x0001)
// Size of packet stored for termination (Proto, bytes)
#define ADDR_TERM_SIZE ((uint16_t)0x0002)

#define DATA_SECTOR_BASE ((uint16_t)0x0003)  // in 32-bits
#define INIT_START DATA_SECTOR_BASE*4 // in 8-bits
#define DATA_SECTOR_END ((uint16_t)0x7FFF)   // in 32-bits (32k767 measurements)

RlncFlashState state = UNSCANNED;

RlncFlashState InitRlncFlashState() {
    uint32_t pageHeader, initSize, termSize;
    auto readStatus = NvmRlnc.Read32(SECTOR_HEADER, &pageHeader);
    if (readStatus != 0x00) {
        return state = READ_FAIL_SECTOR;
    }
    if (pageHeader != 0xFFFF0000) {
        return state = CORRUPT_SECTOR;
    }

    // We set the state to unknown but correct state
    state = NODATA;

    readStatus = NvmRlnc.Read32(ADDR_INIT_SIZE, &initSize);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT;
    }
    if (initSize > INIT_SIZE_LIMIT) {
        return state = CORRUPT_INIT_SIZE;
    }
    readStatus = NvmRlnc.Read32(ADDR_TERM_SIZE, &termSize);
    if (readStatus != 0x00) {
        return state = READ_FAIL_TERM;
    }
    if (termSize > TERM_SIZE_LIMIT) {
        return state = CORRUPT_INIT_SIZE;
    }

    uint8_t buffer[initSize];
    readStatus = NvmRlnc.ReadBuffer8(INIT_START, buffer, initSize);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT_BUFFER;
    }
    flashReadBuffer.clear();
    for (size_t i = 0; i < initSize; i++) {
        flashReadBuffer.push(buffer[i]);
    }
    auto result = initCommand.deserialize(flashReadBuffer);
    if (result != EmbeddedProto::Error::NO_ERRORS) {
        return DESERIALIZE_FAIL_INIT;
    }

    uint8_t bufferTerm[termSize];
    readStatus = NvmRlnc.ReadBuffer8(INIT_START, bufferTerm, termSize);
    if (readStatus != 0x00) {
        return state = READ_FAIL_INIT_BUFFER;
    }
    flashReadBuffer.clear();
    for (size_t i = 0; i < termSize; i++) {
        flashReadBuffer.push(bufferTerm[i]);
    }
    auto resultTerm = terminateCommand.deserialize(flashReadBuffer);
    if (resultTerm != EmbeddedProto::Error::NO_ERRORS) {
        return state = DESERIALIZE_FAIL_TERM;
    }

    return state;
}

RlncFlashState GetRlncFlashState() {
    return state;
}

// Future use
// #define NVM_PAGE2 (7)
// NvmHandle NvmRlnc2(NVM_PAGE2);
