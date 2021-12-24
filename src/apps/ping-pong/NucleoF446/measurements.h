#include <math.h>
#include <stdint.h>

#include "radio_phy.h"

#ifndef MEASUREMENTS_H__
#define MEASUREMENTS_H__

void RegisterNewMeasurement(uint16_t sequenceNumber, uint8_t rssiInv, uint8_t snr);
void ClearMeasurements();
void StreamMeasurements();

#endif  //  MEASUREMENTS_H__
