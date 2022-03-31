#include <stdint.h>

#include "firmware.h"
#include "utilities.h"

#ifndef UTILS_H__
#define UTILS_H__

/**
 * Check that the spreading factor is safe to use
 **/
bool IsValidSpreadingFactor(uint8_t spreadingFactor);

uint32_t EncodeRlncCorrelationCode(uint32_t generationIndex, uint32_t fragmentIndex);

void DecodeRlncFragmentIndex(uint32_t code, uint32_t* fragmentIndex, uint32_t* generationIndex);

DeviceId GetDeviceId();

bool IsDeviceId(const uint32_t& compareId);

#endif  // UTILS_H__
