#ifndef RADIO_PHY__H__
#define RADIO_PHY__H__

#include "cli.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "utils.h"

void InitRadioPhy();
void ProcessSequenceCommand(uint8_t *buffer);
void ParseMsg(uint8_t *RfBuffer, uint8_t msgSize);
void TxBuffer(int16_t dataSize);

void TxNewRFSettings(uint8_t *serialBuf, uint8_t bufSize);
void TxSpreadingFactor(uint8_t value);
void TxSequenceCommand(uint8_t *serialBuf, uint8_t bufSize);
void TxSequenceTestTimerCallback(void *context);
void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs);
void TxTestProcess();

#endif // RADIO_PHY__H__
