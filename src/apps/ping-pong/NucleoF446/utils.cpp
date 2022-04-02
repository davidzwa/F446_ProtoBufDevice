#include "utils.h"

#include "board.h"

bool IsValidSpreadingFactor(uint8_t spreadingFactor) {
    return spreadingFactor >= 7 && spreadingFactor <= 12;
}

void DecodeRlncSequenceNumber(uint32_t code, uint32_t generationTotalSize, uint32_t* fragmentIndex, uint32_t* generationIndex) {
    *fragmentIndex = code % generationTotalSize;
    *generationIndex = (code - *fragmentIndex) / generationTotalSize;
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
