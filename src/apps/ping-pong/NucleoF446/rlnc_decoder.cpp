#include "rlnc_decoder.h"

#include "cli.h"

/*
Galois Field of type GF(2^8)
p(x) = 1x^8+1x^7+0x^6+0x^5+0x^4+0x^3+1x^2+1x^1+1x^0
        1    1    0    0    0    0    1    1    1
*/
unsigned int prim_poly[9] = {1, 0, 0, 0, 1, 1, 1, 0, 1};
galois::GaloisField gf(8, prim_poly);
// Reused symbols in decoding
const galois::GaloisFieldElement nil(&gf, 0);
const galois::GaloisFieldElement pivot(&gf, 1);

#define AUGM_EXCEPTION "Bad matrix augmentation size"

#define MAX_GEN_SIZE 5
#define MAX_OVERHEAD 2
#define MAX_SYMBOLS 12

RlncDecoder::RlncDecoder() {
    lfsr = new LFSR(LFSR_DEFAULT_SEED);
    terminated = true;

    // Make this matrix statically allocated - ensure it's larger than needed
    decodingMatrix = vector(MAX_GEN_SIZE + MAX_OVERHEAD, vector<galois::GFSymbol>(MAX_SYMBOLS + MAX_GEN_SIZE));
}

void RlncDecoder::InitRlncDecodingSession(RlncInitConfigCommand& rlncInitConfig) {
    // TODO error out if already running a decoding session?
    // TODO what if generationSize is too big? Device will crash most probably...

    // Save state config
    rlncDecodingConfig = rlncInitConfig;

    terminated = false;
    generationIndex = 0;

    // Apply to LFSR
    lfsr->Seed = rlncInitConfig.get_LfsrSeed();
    lfsr->Reset();

    // Prepare storage for the configured generation
    PrepareFragmentStorage();
    
    ClearDecodingMatrix();
}

void RlncDecoder::PrepareFragmentStorage() {
    generationFrames.clear();
    // Quite conservative (2 overhead) - does not assume any dependent vectors arrive
    generationFrames.reserve(rlncDecodingConfig.get_GenerationSize() + 2);
}

void RlncDecoder::ClearDecodingMatrix() {
    for (uint8_t i = 0; i < decodingMatrix.size(); i++) {
        decodingMatrix[i].clear();
    }

    decodingMatrix.clear();
    storedPackets = 0;
}

void RlncDecoder::ProcessRlncFragment(LORA_MSG_TEMPLATE& message) {
    // Fetch the encoding vector length
    auto generationSize = rlncDecodingConfig.get_GenerationSize();

    // Generate the encoding vector
    vector<SYMB> encodingVector;
    lfsr->GenerateMany(encodingVector, generationSize);

    // Process the fragment as augmented vector from frame and enc vector
    // generationFrames.size() * (size(frame) + size(enc))
    RlncFrame frame(encodingVector, message.Payload(), message.get_Payload().get_length());

    // Store the frame in safe memory
    generationFrames.push_back(frame);
    // Store the frame as malleable matrix row
    AddFrameAsMatrixRow(generationFrames.size() - 1);

    if (generationFrames.size() >= generationSize) {
        // Enough packets have arrived to attempt decoding with high probability
        auto decodingResult = DecodeFragments();

        // Delegate to Flash, UART or LoRa
        StoreDecodingResult(decodingResult);
    }
}

void RlncDecoder::UpdateRlncDecodingState(RlncStateUpdate& rlncStateUpdate) {
    // Update state
    lfsr->State = rlncStateUpdate.get_LfsrState();
    generationIndex = rlncStateUpdate.get_GenerationIndex();

    // Prepare for next generation
    ClearDecodingMatrix();
    PrepareFragmentStorage();
}

void RlncDecoder::TerminateRlnc(RlncTerminationCommand& RlncTerminationCommand) {
    // Reduce memory usage
    generationFrames.clear();
    generationIndex = 0;
    ClearDecodingMatrix();

    // Debugging flag for tracking the state
    terminated = true;
}

RlncDecodingResult RlncDecoder::DecodeFragments() {
    RlncDecodingResult result;
    result.generationIndex = generationIndex;

    // Get the symbols to skip in RREF
    auto fragmentSymbols = rlncDecodingConfig.get_FrameSize();
    ReduceMatrix(fragmentSymbols);

    // Verify decoding success and do packet integrity check

    // Pass the result to be stored/propagated
    result.success = true;
    return result;
}

void RlncDecoder::StoreDecodingResult(RlncDecodingResult& decodingResult) {
    // Bring the generation decoded result to 'flash', 'UART', 'LoRa' or evaporate it
    if (!decodingResult.success) {
        // Store failure?
        return;
    } else {
        // Store success
        return;
    }
}

void RlncDecoder::AddFrameAsMatrixRow(uint8_t row) {
    auto source = generationFrames[row].augVector;

    // TODO test whether this copies correctly
    this->decodingMatrix[row].assign(source.begin(), source.end());

    // Keep track of reduced/non-reduced packets equally
    storedPackets++;
}

uint8_t RlncDecoder::DetermineMatrixRank() {
    // generationSize is the dimension for our square submatrix (encoding matrix)
    auto generationSize = rlncDecodingConfig.get_GenerationSize();

    bool currentRowAllZeroes = true;
    for (uint8_t i; i < generationSize; i++) {
        for (uint8_t j; j < generationSize; j++) {
            // If we spot one value not equal to 1, we should move on
            if (decodingMatrix[i][j] != 0) {
                currentRowAllZeroes = false;
                break;
            }
        }

        if (currentRowAllZeroes) return i;
    }

    return generationSize;
}

void RlncDecoder::ReduceMatrix(uint8_t augmentedCols) {
    auto totalRowCount = decodingMatrix.size();
    auto totalColCount = decodingMatrix[0].size();

    if (totalColCount >= augmentedCols) {
        UartThrow(AUGM_EXCEPTION, sizeof(AUGM_EXCEPTION));
        throw "Bad matrix augmentation size";
    }

    uint8_t numPivots = 0;

    // loop through columns, exclude augmented columns
    for (uint8_t col = 0; col < totalColCount - augmentedCols; col++) {
        auto pivotRow = FindPivot(numPivots, col, totalRowCount);

        if (!pivotRow.has_value())
            continue;  // no pivots, go to another column

        ReduceRow(pivotRow.value(), col, totalColCount);

        SwitchRows(pivotRow.value(), numPivots, totalColCount);

        pivotRow = numPivots;
        numPivots++;

        // Require Reduced form unconditionally
        // if (form == MatrixReductionForm.ReducedRowEchelonForm)
        for (uint8_t tmpRow = 0; tmpRow < pivotRow.value(); tmpRow++)
            EliminateRow(tmpRow, pivotRow.value(), col, totalColCount);

        // Eliminate Next Rows
        for (uint8_t tmpRow = pivotRow.value(); tmpRow < totalRowCount; tmpRow++)
            EliminateRow(tmpRow, pivotRow.value(), col, totalColCount);
    }
}

optional<uint8_t> RlncDecoder::FindPivot(uint8_t startRow, uint8_t col, uint8_t rowCount) {
    for (uint8_t i = startRow; i < rowCount; i++) {
        if (decodingMatrix[i][col] != nil.poly())
            return i;
    }

    return NULL;
}

void RlncDecoder::SwitchRows(uint8_t row1, uint8_t row2, uint8_t colCount) {
    if (row1 == row2) return;

    for (auto col = 0; col < colCount; col++) {
        // Error
        // Row1 == 0x0
        // Row2 == 0x10?
        // colCount = 4?
        swap(decodingMatrix[row1][col], decodingMatrix[row2][col]);
    }
}

void RlncDecoder::ReduceRow(uint8_t row, uint8_t col, uint8_t colCount) {
    auto coefficient = pivot / galois::GaloisFieldElement(&gf, decodingMatrix[row][col]);
    if (coefficient == pivot) return;

    for (; col < colCount; col++) {
        decodingMatrix[row][col] *= coefficient.poly();
    }
}

void RlncDecoder::EliminateRow(uint8_t row, uint8_t pivotRow, uint8_t pivotCol, uint8_t colCount) {
    if (pivotRow == row) {
        return;
    }

    if (galois::GaloisFieldElement(&gf, decodingMatrix[row][pivotCol]) == nil) {
        return;
    }
}
