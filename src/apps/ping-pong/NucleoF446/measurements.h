#include <math.h>
#include <stdint.h>

#include "measurements_nvmm.h"
#include "radio_phy.h"

#ifndef MEASUREMENTS_H__
#define MEASUREMENTS_H__

void InitializeMeasurements();
bool IsStorageDirtyAndLocked();
void RegisterNewMeasurement(uint16_t sequenceNumber, int16_t rssi, int8_t snr);
void ClearMeasurements();
void RequestStreamMeasurements(/* DeviceId */);
void StreamMeasurements();

#endif  //  MEASUREMENTS_H__
