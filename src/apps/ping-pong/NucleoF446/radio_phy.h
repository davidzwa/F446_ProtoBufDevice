#include "ProtoWriteBuffer.h"
#include "config.h"
#include "radio.h"
#include "stdint.h"
#include "lora_device_messages.h"

#ifndef RADIO_PHY__H__
#define RADIO_PHY__H__

void InitRadioPhy();
void TransmitSpreadingFactorConfig(uint8_t spreadingFactor);

void TransmitLoRaMessage(LORA_MSG_TEMPLATE& message);

void TxSequenceCommand(uint8_t *serialBuf, uint8_t bufSize);
void TxSequenceTestTimerCallback(void *context);
void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs);
void TxTestProcess();

#endif // RADIO_PHY__H__
