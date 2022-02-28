#ifndef RLNC_DECODER_H__
#define RLNC_DECODER_H__

#include "GaloisFieldElement.h"
#include "lora_device_messages.h"

class RlncDecoder {
    public:
     RlncDecoder();
    
     void InitRlncDecodingSession(RlncInitConfigCommand& configCommand);
     void ProcessRlncFragment(RlncEncodedFragment& rlncEncodedFragment);
     void UpdateRlncDecodingState(RlncStateUpdate& rlncStateUpdate);
     void TerminateRlnc(RlncTerminationCommand& RlncTerminationCommand);

     uint8_t GetNextLFSRState();
};

#endif  // RLNC_DECODER_H__
