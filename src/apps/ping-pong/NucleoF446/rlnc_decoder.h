#ifndef RLNC_DECODER_H__
#define RLNC_DECODER_H__

#include <stdint.h>
#include <vector>

#include "GaloisFieldElement.h"
#include "LinearFeedbackShiftRegister.h"
#include "config.h"
#include "lora_device_messages.h"
#include "rlnc_decoding_result.h"
#include "rlnc_frame.h"

using namespace std;

class RlncDecoder {
   public:
    RlncDecoder();

    void InitRlncDecodingSession(RlncInitConfigCommand& configCommand);
    void ProcessRlncFragment(LORA_MSG_TEMPLATE& message);
    void UpdateRlncDecodingState(const RlncStateUpdate& rlncStateUpdate);
    void TerminateRlnc(const RlncTerminationCommand& RlncTerminationCommand);

    // Debugging function
    // SYMB RlncDecoder::GetNextLFSRState() {
    //     return lfsr->Generate();
    // }

   protected:
    void AddFrameAsMatrixRow(uint8_t row);
    void ReduceMatrix(uint8_t augmentedCols);
    optional<uint8_t> FindPivot(uint8_t startRow, uint8_t col, uint8_t rowCount);
    void SwitchRows(uint8_t row1, uint8_t row2, uint8_t colCount);
    void ReduceRow(uint8_t row, uint8_t col, uint8_t colCount);
    void EliminateRow(uint8_t row, uint8_t pivotRow, uint8_t pivotCol, uint8_t colCount);
    uint8_t DetermineMatrixRank();

   private:
    void PrepareFragmentStorage();
    void ClearDecodingMatrix();
    uint32_t GetEncodingVectorLength();
    RlncDecodingResult DecodeFragments();
    void StoreDecodingResult(RlncDecodingResult& decodingResult);
    LFSR* lfsr;
    uint8_t generationIndex;
    bool terminated;
    RlncInitConfigCommand rlncDecodingConfig;

    // Static storage
    vector<RlncFrame> generationFrames;

    // Expensive matrix
    uint8_t storedPackets = 0;
    vector<vector<galois::GFSymbol>> decodingMatrix;
};

#endif  // RLNC_DECODER_H__
