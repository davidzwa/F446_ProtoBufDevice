#include <stdint.h>

#include "device_messages.h"

#ifndef UTILS_H__
#define UTILS_H__

/**
 * Check that the spreading factor is safe to use
 **/
bool IsValidSpreadingFactor(uint8_t spreadingFactor);

DeviceId GetDeviceId();

#endif // UTILS_H__
