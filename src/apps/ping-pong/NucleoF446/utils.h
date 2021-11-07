#include <stdint.h>

#ifndef UTILS_H__
#define UTILS_H__

typedef struct DeviceId_s {
    uint32_t id0;
    uint32_t id1;
    uint32_t id2;
} DeviceId_t;

/**
 * Check that the spreading factor is safe to use
 **/
bool IsValidSpreadingFactor(uint8_t spreadingFactor);

DeviceId_t GetDeviceId();

#endif // UTILS_H__
