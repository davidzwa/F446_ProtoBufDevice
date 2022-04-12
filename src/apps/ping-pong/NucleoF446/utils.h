#include <stdint.h>

#include "firmware.h"
#include "utilities.h"

#ifndef UTILS_H__
#define UTILS_H__

/**
 * Check that the spreading factor is safe to use
 **/
bool IsValidSpreadingFactor(uint8_t spreadingFactor);

void DecodeRlncSequenceNumber(uint32_t code, uint32_t generationTotalSize, uint32_t* fragmentIndex, uint32_t* generationIndex);

DeviceId GetDeviceId();

bool IsDeviceId(const uint32_t& compareId);

uint32_t BytesToInt(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);

#endif  // UTILS_H__
