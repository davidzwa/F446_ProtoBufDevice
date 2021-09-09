#include <stdint.h>

#ifndef UTILS_H__
#define UTILS_H__

typedef struct DeviceId_s {
    uint32_t id0;
    uint32_t id1;
    uint32_t id2;
} DeviceId_t;

DeviceId_t GetDeviceId();
int MapSpreadingFactor(uint8_t value);


#endif // UTILS_H__