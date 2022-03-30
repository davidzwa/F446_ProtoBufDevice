#include "utils.h"

#include "board.h"

#define MULT_GEN (1000000U)

bool IsValidSpreadingFactor(uint8_t spreadingFactor) {
    return spreadingFactor >= 7 && spreadingFactor <= 12;
}

uint32_t EncodeRlncCorrelationCode(uint32_t generationIndex, uint32_t fragmentIndex) {
    return generationIndex * MULT_GEN + fragmentIndex;
}

void DecodeRlncFragmentIndex(uint32_t code, uint32_t* fragmentIndex, uint32_t* generationIndex) {
    *fragmentIndex = code % MULT_GEN;
    *generationIndex = (code - *fragmentIndex) / MULT_GEN;
}

DeviceId GetDeviceId() {
    DeviceId deviceId;

    deviceId.set_Id0(BoardGetHwUUID0());
    deviceId.set_Id1(BoardGetHwUUID1());
    deviceId.set_Id2(BoardGetHwUUID2());

    return deviceId;
}

bool IsDeviceId(const uint32_t& compareId) {
    auto currentId = GetDeviceId();
    return compareId == currentId.Id0();
}
