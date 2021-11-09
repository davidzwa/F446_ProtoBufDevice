#include "stdint.h"

#ifndef RADIO_PHY__H__
#define RADIO_PHY__H__

void InitRadioPhy();
void TransmitSpreadingFactorConfig(uint8_t spreadingFactor);

void TxSequenceCommand(uint8_t *serialBuf, uint8_t bufSize);
void TxSequenceTestTimerCallback(void *context);
void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs);
void TxTestProcess();

#endif // RADIO_PHY__H__
