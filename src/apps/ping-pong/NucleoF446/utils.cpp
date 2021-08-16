#include "utils.h"
#include "board.h"

int MapSpreadingFactor(uint8_t value)
{
    if (value == '7')
    {
        return 7;
    }
    else if (value == '8')
    {
        return 8;
    }
    else if (value == '9')
    {
        return 9;
    }
    else if (value == '0')
    {
        return 10;
    }
    else if (value == '1')
    {
        return 11;
    }
    else if (value == '2')
    {
        return 12;
    }

    return -1;
}

DeviceId_t GetDeviceId() {
    DeviceId_t deviceId = {
        .id0=BoardGetHwUUID0(),
        .id1=BoardGetHwUUID1(),
        .id2=BoardGetHwUUID2(),
    };
    return deviceId;
}