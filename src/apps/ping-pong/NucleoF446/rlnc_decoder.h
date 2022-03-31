#ifndef RLNC_DECODER_H__
#define RLNC_DECODER_H__

#include <stdint.h>

#include <vector>

#include "GaloisFieldElement.h"
#include "LinearFeedbackShiftRegister.h"
#include "config.h"
#include "lora_device_messages.h"

using namespace std;

#define SYMB uint8_t

enum DecodingError {
    AUGMENTED_COLS_EXCEEDS_TOTAL = 0x01,
    FRAME_SIZE_MISMATCH = 0x02,
    MATRIX_SIZE_0_ADD_ROW = 0x03,
    FIND_PIVOT_ROWCOUNT_0 = 0x04,
    INNO_ROW_EXCEEDS_MATRIX_ROWS = 0x05,
    INNO_ROW_EXCEEDS_MATRIX_COLS = 0x06,
    ILLEGAL_RANK_STATE = 0x07 // Usually a corrupt matrix (bit-flips?)
};

class RlncDecoder {
   public:
    RlncDecoder();

    void InitRlncDecodingSession(RlncInitConfigCommand& configCommand);
    void ProcessRlncFragment(LORA_MSG_TEMPLATE& message);
    void UpdateRlncDecodingState(const RlncStateUpdate& rlncStateUpdate);
    void AutoTerminateRlnc();
    void TerminateRlnc(const RlncTerminationCommand& RlncTerminationCommand);

   protected:
    void ThrowDecodingError(DecodingError error);
    uint8_t AddFrameAsMatrixRow(vector<SYMB>& row);
    void ReduceMatrix(uint8_t augmentedCols);
    void DebugSendMatrix();
    optional<uint8_t> FindPivot(uint8_t startRow, uint8_t col, uint8_t rowCount);
    void SwitchRows(uint8_t row1, uint8_t row2, uint8_t colCount);
    void ReduceRow(uint8_t row, uint8_t col, uint8_t colCount);
    void EliminateRow(uint8_t row, uint8_t pivotRow, uint8_t pivotCol, uint8_t colCount);
    uint8_t DetermineNextInnovativeRowIndex();

   private:
    bool DecidePacketErrorDroppage(bool isUpdatePacket);
    void ReserveGenerationStorage();
    void ClearDecodingMatrix();

    uint32_t GetMatrixColumnCount();
    uint32_t GetEncodingVectorLength();
    void DecodeFragments(DecodingResult& result);
    void SendUartDecodingResult(DecodingResult& result);
    void StoreDecodingResult(DecodingResult& decodingResult);

    RlncInitConfigCommand rlncConfig;
    LFSR* lfsr;
    uint8_t generationIndex;
    bool generationSucceeded;
    uint16_t receivedGenFragments;
    uint16_t missedGenFragments;
    bool terminated;
    vector<vector<galois::GFSymbol>> decodingMatrix;
};

#endif  // RLNC_DECODER_H__
