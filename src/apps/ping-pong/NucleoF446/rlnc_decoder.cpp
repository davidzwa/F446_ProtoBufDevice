#include "rlnc_decoder.h"

#include "Crc8.h"
#include "cli.h"
#include "utilities.h"

unsigned int prim_poly = 0x11D;
galois::GaloisField gf(8, prim_poly);

#define AUGM_EXCEPTION "Bad matrix augmentation size"

#define MAX_GEN_SIZE 5
#define MAX_OVERHEAD 2
#define MAX_SYMBOLS 12

void SendUartTermination() {
    UartDebug("RLNC_TERMINATE", 0, 15);
}

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
    ClearDecodingMatrix();
    ReserveGenerationStorage();
}

void RlncDecoder::ReserveGenerationStorage() {
    ClearGenerationStorage();
    // Quite conservative (2 overhead) - does not assume any dependent vectors arrive
    generationFrames.reserve(rlncDecodingConfig.get_GenerationSize() + 2);
}

void RlncDecoder::ClearGenerationStorage() {
    for (uint8_t i = 0; i < generationFrames.size(); i++) {
        // fill(generationFrames[i].augVector.begin(), generationFrames[i].augVector.end(), 0);
        generationFrames[i].augVector.clear();
    }
    generationFrames.clear();
}

void RlncDecoder::ClearDecodingMatrix() {
    for (uint8_t i = 0; i < decodingMatrix.size(); i++) {
        // fill(decodingMatrix[i].begin(), decodingMatrix[i].end(), 0);
        decodingMatrix[i].clear();
    }

    decodingMatrix.clear();
}

uint32_t RlncDecoder::GetGenerationFragmentCount() {
    auto generationSize = rlncDecodingConfig.get_GenerationSize();
    auto processedFrames = (this->generationIndex * generationSize);
    auto totalFrameCountLeft = rlncDecodingConfig.get_TotalFrameCount() - processedFrames;

    // If the total frame count left-over is less than the generation size, we take that
    if (generationSize <= totalFrameCountLeft) {
        return generationSize;
    } else {
        return totalFrameCountLeft;
    }
}

void RlncDecoder::ProcessRlncFragment(LORA_MSG_TEMPLATE& message) {
    // Fetch the encoding vector length
    auto minimalFragmentCount = GetGenerationFragmentCount();

    // Generate the encoding vector
    vector<SYMB> encodingVector;
    auto lfsrResetState = message.get_rlncEncodedFragment().get_LfsrState();

    lfsr->State = lfsrResetState;
    lfsr->GenerateMany(encodingVector, minimalFragmentCount);

    // Process the fragment as augmented vector from frame and enc vector
    // generationFrames.size() * (size(frame) + size(enc))
    RlncFrame frame(encodingVector, message.Payload(), message.get_Payload().get_length());

    // Store the frame in safe memory
    // auto matrixCapacity = decodingMatrix.capacity();
    generationFrames.push_back(frame);
    // Store the frame as malleable matrix row
    auto lastRowIndex = generationFrames.size() - 1;
    AddFrameAsMatrixRow(lastRowIndex);

    DecodingResult result;

    // Debug previous decoding action and any new packet
    uint8_t crc1 = ComputeChecksum(decodingMatrix[0].data(), decodingMatrix[0].size());
    uint8_t crc2 = ComputeChecksum(decodingMatrix[lastRowIndex].data(), decodingMatrix[0].size());
    DecodingUpdate decodingUpdate;
    decodingUpdate.set_RankProgress(DetermineDecodingProgress());
    decodingUpdate.set_ReceivedFragments(generationFrames.size());
    decodingUpdate.set_CurrentGenerationIndex(generationIndex);
    decodingUpdate.set_IsRunning(!terminated);
    decodingUpdate.set_UsedLfsrState(lfsrResetState);
    decodingUpdate.set_CurrentLfsrState(lfsr->State);
    decodingUpdate.set_FirstRowCrc8(crc1);
    decodingUpdate.set_LastRowCrc8(crc2);
    decodingUpdate.set_LastRowIndex(lastRowIndex);
    // Contains the untouched frame, so send before decoding
    UartSendDecodingUpdate(decodingUpdate, frame.augVector.data(), frame.augVector.size());

    // Decoding should not fail when incomplete
    DecodeFragments(result);

    // Process the results - if any
    if (generationFrames.size() >= minimalFragmentCount) {
        // Enough packets have arrived to attempt decoding with high probability
        // DecodeFragments(result);

        // Verify decoding success and do packet integrity check
        auto encVectorLength = GetGenerationFragmentCount();
        auto progress = DetermineDecodingProgress();
        auto numberColumn = encVectorLength + 3;  // 4th byte is a fixated column
        auto firstNumber = decodingMatrix[0][numberColumn];
        auto lastRowIndex = encVectorLength - 1;
        auto lastNumber = (uint8_t)(progress >= encVectorLength ? decodingMatrix[lastRowIndex][numberColumn] : 0x00);

        result.set_Success(firstNumber == 0x00 && lastNumber == (encVectorLength - 1));
        result.set_MatrixRank(progress);
        result.set_FirstDecodedNumber(firstNumber);
        result.set_LastDecodedNumber(lastNumber);
        UartSendDecodingResult(result);

        // Delegate to Flash, UART or LoRa
        // StoreDecodingResult(result);

        if (result.Success()) {
            AutoTerminateRlnc();
        }
    }
}

void RlncDecoder::DecodeFragments(DecodingResult& result) {
    CRITICAL_SECTION_BEGIN();

    // Get the symbols to skip in RREF
    auto augLength = rlncDecodingConfig.get_FrameSize();
    ReduceMatrix(augLength);

    CRITICAL_SECTION_END();
}

/**
 * @brief Update the state to move or reset generation
 *
 * @param rlncStateUpdate
 */
void RlncDecoder::UpdateRlncDecodingState(const RlncStateUpdate& rlncStateUpdate) {
    // Update state
    lfsr->State = rlncStateUpdate.get_LfsrState();
    generationIndex = rlncStateUpdate.get_GenerationIndex();

    // Prepare for next generation
    ClearDecodingMatrix();
    ReserveGenerationStorage();
}

void RlncDecoder::TerminateRlnc(const RlncTerminationCommand& RlncTerminationCommand) {
    AutoTerminateRlnc();
}

void RlncDecoder::AutoTerminateRlnc() {
    // Reset state
    generationIndex = 0xFF;
    lfsr->Reset();
    ClearDecodingMatrix();
    ClearGenerationStorage();

    // Debugging flag for tracking the state
    terminated = true;
    SendUartTermination();
}

void RlncDecoder::StoreDecodingResult(DecodingResult& decodingResult) {
    // Bring the generation decoded result to 'flash', 'UART', 'LoRa' or evaporate it
    if (!decodingResult.Success()) {
        // Store failure?
        // TODO
        return;
    } else {
        // Store success
        // TODO
        return;
    }
}

void RlncDecoder::AddFrameAsMatrixRow(uint8_t rowIndex) {
    auto source = generationFrames[rowIndex].augVector;

    // TODO test whether this copies correctly
    vector<galois::GFSymbol> newData;
    newData.assign(source.begin(), source.end());
    this->decodingMatrix.push_back(newData);
}

uint8_t RlncDecoder::DetermineDecodingProgress() {
    // generationSize is the dimension for our square submatrix (encoding matrix)
    auto encodingVectorColumnCount = GetGenerationFragmentCount();

    bool currentRowAllZeroes = true;
    for (uint8_t i; i < decodingMatrix.size(); i++) {
        for (uint8_t j; j < encodingVectorColumnCount; j++) {
            // We assume RREF, so any non-unity diagonal entry means rank is the row index
            if (i == j && decodingMatrix[i][j] != 1) {
                return i;
            }
            // If we spot one value not equal to 0, we have to check
            if (decodingMatrix[i][j] != 0) {
                currentRowAllZeroes = false;
                break;
            }
        }

        if (currentRowAllZeroes) return i;
    }

    // If no row is all-0 we have full rank
    return encodingVectorColumnCount;
}

void RlncDecoder::ReduceMatrix(uint8_t augmentedCols) {
    auto totalRowCount = decodingMatrix.size();
    auto totalColCount = decodingMatrix[0].size();

    if (augmentedCols >= totalColCount) {
        UartThrow(AUGM_EXCEPTION, sizeof(AUGM_EXCEPTION) - 1);
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
        for (uint8_t tmpRow = 0; tmpRow < pivotRow.value(); tmpRow++)
            EliminateRow(tmpRow, pivotRow.value(), col, totalColCount);

        // Eliminate Next Rows
        for (uint8_t tmpRow = pivotRow.value(); tmpRow < totalRowCount; tmpRow++)
            EliminateRow(tmpRow, pivotRow.value(), col, totalColCount);
    }
}

optional<uint8_t> RlncDecoder::FindPivot(uint8_t startRow, uint8_t col, uint8_t rowCount) {
    if (rowCount == 0) {
        throw "Illegal rowcount given";
    }

    for (uint8_t i = startRow; i < rowCount; i++) {
        if (decodingMatrix[i][col] != galois::nil)
            return i;
    }

    return NULL;
}

void RlncDecoder::SwitchRows(uint8_t row1, uint8_t row2, uint8_t colCount) {
    if (row1 == row2) return;

    for (auto col = 0; col < colCount; col++) {
        swap(decodingMatrix[row1][col], decodingMatrix[row2][col]);
    }
}

void RlncDecoder::ReduceRow(uint8_t row, uint8_t col, uint8_t colCount) {
    auto coefficient = gf.div(galois::unity, decodingMatrix[row][col]);

    if (coefficient == galois::unity) return;

    for (; col < colCount; col++) {
        decodingMatrix[row][col] = gf.mul(decodingMatrix[row][col], coefficient);
    }
}

void RlncDecoder::EliminateRow(uint8_t row, uint8_t pivotRow, uint8_t pivotCol, uint8_t colCount) {
    if (pivotRow == row) {
        return;
    }

    if (decodingMatrix[row][pivotCol] == galois::nil) {
        return;
    }

    auto coefficient = decodingMatrix[row][pivotCol];
    for (int col = pivotCol; col < colCount; col++) {
        decodingMatrix[row][col] = gf.sub(decodingMatrix[row][col], gf.mul(decodingMatrix[pivotRow][col], coefficient));
    }
}
