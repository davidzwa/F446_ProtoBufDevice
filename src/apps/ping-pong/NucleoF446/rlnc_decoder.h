#ifndef RLNC_DECODER_H__
#define RLNC_DECODER_H__

#include <vector>
#include <stdint.h>

#include "GaloisFieldElement.h"
#include "LinearFeedbackShiftRegister.h"
#include "config.h"
#include "lora_device_messages.h"
#include "rlnc_frame.h"
#include "rlnc_decoding_result.h"

using namespace std;

#define SYMB uint8_t

class RlncDecoder {
   public:
    RlncDecoder();

    void InitRlncDecodingSession(RlncInitConfigCommand& configCommand);
    void ProcessRlncFragment(SYMB* payload, uint8_t payloadLength);
    void UpdateRlncDecodingState(RlncStateUpdate& rlncStateUpdate);
    void TerminateRlnc(RlncTerminationCommand& RlncTerminationCommand);

    // Debugging function
    uint8_t GetNextLFSRState();

   private:
    void PrepareFragmentStorage();
    void ClearDecodingMatrix();
    RlncDecodingResult
    DecodeFragments();
    void StoreDecodingResult(RlncDecodingResult& decodingResult);
    LFSR* lfsr;
    uint8_t generationIndex;
    bool terminated;
    RlncInitConfigCommand rlncDecodingConfig;
    
    // Static storage
    vector<RlncFrame> generationFrames;

    // Expensive matrix
    vector<vector<SYMB>> decodingMatrix;
};

#endif  // RLNC_DECODER_H__
