#ifndef RLNC_DECODER_H__
#define RLNC_DECODER_H__

#include "lora_device_messages.h"
#include "GaloisFieldElement.h"

void InitRlncDecodingSession(RlncInitConfigCommand& configCommand);
void UpdateRlncDecodingState(RlncStateUpdate& rlncStateUpdate);

uint8_t GetNextLFSRState();

#endif  // RLNC_DECODER_H__
