#include <stdint.h>

#include "firmware.h"

#ifndef UTILS_H__
#define UTILS_H__

/**
 * Check that the spreading factor is safe to use
 **/
bool IsValidSpreadingFactor(uint8_t spreadingFactor);

DeviceId GetDeviceId();

bool IsDeviceId(const uint32_t& compareId);

#endif // UTILS_H__
