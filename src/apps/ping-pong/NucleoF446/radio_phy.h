#include "ProtoWriteBuffer.h"
#include "config.h"
#include "lora_device_messages.h"
#include "radio.h"
#include "rlnc_decoder.h"
#include "stdint.h"

#ifndef RADIO_PHY__H__
#define RADIO_PHY__H__

static RlncDecoder decoder;

uint32_t InitRadioPhy();
void TransmitSpreadingFactorConfig(uint8_t spreadingFactor);
void TransmitLoRaMessage(LORA_MSG_TEMPLATE& message);
void TransmitLoRaFlashInfo(bool wasCleared);

void TxSequenceCommand(uint8_t* serialBuf, uint8_t bufSize);
void TxSequenceTestTimerCallback(void *context);
void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs);
void TxLoRaAck(int correlationCode);
void TxTestProcess();

// For handling uart test messages through our processing pipeline
bool HandleLoRaProtoPayload(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr);

#endif // RADIO_PHY__H__
