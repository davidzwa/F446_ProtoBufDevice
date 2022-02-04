#include <math.h>
#include <stdint.h>

#include "measurements_nvmm.h"
#include "radio_phy.h"

#ifndef MEASUREMENTS_H__
#define MEASUREMENTS_H__

// Limit based on self-enforced size minus some margin - making it 40 => 10 measurements
#define MEASUREMENT_FRAGMENT_SIZE (MAX_LORA_BYTES-10)

void InitializeMeasurements();
bool IsStorageDirtyAndLocked();
void RegisterNewMeasurement(uint16_t sequenceNumber, int16_t rssi, int8_t snr);
void ClearMeasurements();
void RequestStreamMeasurements(/* DeviceId */);
void StreamMeasurements();

#endif  //  MEASUREMENTS_H__
