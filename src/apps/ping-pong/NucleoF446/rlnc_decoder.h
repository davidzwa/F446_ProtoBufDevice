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
    void ProcessRlncFragment(SYMB* payload, uint8_t payloadLength);
    void UpdateRlncDecodingState(RlncStateUpdate& rlncStateUpdate);
    void TerminateRlnc(RlncTerminationCommand& RlncTerminationCommand);

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

// float A[3][4] = {{5, -6, -7, 7},
//                  {3, -2, 5, -17},
//                  {2, 4, -3, 29}};  // answer should be {2, 4, -3}
// RowReduce(A);

// https://rosettacode.org/wiki/Reduced_row_echelon_form
// https://stackoverflow.com/questions/31756413/solving-a-simple-matrix-in-row-reduced-form-in-c
// void RowReduce(float A[][4]) {
//     const int nrows = 3;  // number of rows
//     const int ncols = 4;  // number of columns

//     int lead = 0;

//     while (lead < nrows) {
//         float d, m;

//         for (int r = 0; r < nrows; r++) {  // for each row ...
//             /* calculate divisor and multiplier */
//             d = A[lead][lead];
//             m = A[r][lead] / A[lead][lead];

//             for (int c = 0; c < ncols; c++) {  // for each column ...
//                 if (r == lead)
//                     A[r][c] /= d;  // make pivot = 1
//                 else
//                     A[r][c] -= A[lead][c] * m;  // make other = 0
//             }
//         }

//         lead++;
//     }
// }
