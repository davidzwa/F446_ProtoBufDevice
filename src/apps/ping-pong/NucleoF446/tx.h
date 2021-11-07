#include "radio.h"
#include "config.h"
#include "rx.h"
#include "delay.h"
#include "stdio.h"
#include "timer.h"

#ifndef TX_H__
#define TX_H__

void TxBuffer(int16_t dataSize);
void TxPing();
void TxPong();

void TxNewRFSettings(uint8_t *serialBuf, uint8_t bufSize);

void TxSpreadingFactor(uint8_t value);

void TxSequenceCommand(uint8_t *serialBuf, uint8_t bufSize);
void TxSequenceTestTimerCallback( void* context);
void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs);
void TxTestProcess();

#endif // TX_H__
