#include "utils.h"

#include "board.h"

bool IsValidSpreadingFactor(uint8_t spreadingFactor) {
    return spreadingFactor >= 7 && spreadingFactor <= 12;
}

DeviceId_t GetDeviceId() {
    DeviceId_t deviceId = {
        .id0 = BoardGetHwUUID0(),
        .id1 = BoardGetHwUUID1(),
        .id2 = BoardGetHwUUID2(),
    };
    return deviceId;
}
