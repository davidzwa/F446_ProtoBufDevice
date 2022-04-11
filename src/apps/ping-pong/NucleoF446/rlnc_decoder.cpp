#include "rlnc_decoder.h"

#include "Crc8.h"
#include "cli.h"
#include "delay.h"
#include "utilities.h"
#include "utils.h"

unsigned int prim_poly = 0x11D;
galois::GaloisField gf(8, prim_poly);
static DecodingResult lastDecodingResult;
#define MAX_GEN_SIZE 5
#define MAX_OVERHEAD 2
#define MAX_SYMBOLS 12

using namespace std;
using namespace xoshiro_detail;

void SendUartTermination() {
    UartDebug("RLNC_TERMINATE", 0, 15);
}

RlncDecoder::RlncDecoder() {
    
    rng = xoshiro32starstar8(0x00, 0x00, 0x00, 0x01);
    terminated = true;

    // Make this matrix statically allocated - ensure it's larger than needed
    decodingMatrix = vector(MAX_GEN_SIZE + MAX_OVERHEAD, vector<galois::GFSymbol>(MAX_SYMBOLS + MAX_GEN_SIZE));
}

void RlncDecoder::InitRlncDecodingSession(RlncInitConfigCommand& rlncInitConfig) {
    // TODO error out if already running a decoding session?
    // TODO what if generationSize is too big? Device will crash most probably...

    // Save state config
    rlncConfig = rlncInitConfig;

    // Set the random seed if applicable
    auto receptionConfig = rlncConfig.get_receptionRateConfig();
    if (receptionConfig.get_OverrideSeed()) {
        srand1(receptionConfig.get_Seed());
        UartDebug("RLNC_PER_SEED", GetSeed(), 13);
    }

    terminated = false;
    generationIndex = 0;
    generationSucceeded = false;
    atLeastGenerationResultSent = false;

    // Prepare storage for the configured generation
    ReserveGenerationStorage();
}

void RlncDecoder::ReserveGenerationStorage() {
    ClearDecodingMatrix();
    receivedGenFragments = 0;
    missedGenFragments = 0;

    // We only need independent/innovative packets which is at most min(generation_size, left_frames)
    auto fragmentsNeeded = GetEncodingVectorLength();
    auto colsNeeded = GetMatrixColumnCount();

    decodingMatrix.resize(fragmentsNeeded);
    for (uint32_t i = 0; i < fragmentsNeeded; i++) {
        decodingMatrix[i].resize(colsNeeded);
        decodingMatrix[i].assign(colsNeeded, 0);
    }
}

void RlncDecoder::ClearDecodingMatrix() {
    for (uint8_t i = 0; i < decodingMatrix.size(); i++) {
        decodingMatrix[i].clear();
    }
    decodingMatrix.clear();
}

uint32_t RlncDecoder::GetMatrixColumnCount() {
    auto encodingVectorLength = GetEncodingVectorLength();
    auto fragmentLength = rlncConfig.get_FrameSize();

    return fragmentLength + encodingVectorLength;
}

/**
 * @brief Gets the encoding vector length, which is equal to the amount of innovative fragments in the mixture
 *
 * @return uint32_t
 */
uint32_t RlncDecoder::GetEncodingVectorLength() {
    auto generationSize = rlncConfig.get_GenerationSize();
    auto processedFrames = (this->generationIndex * generationSize);
    auto totalFrameCountLeft = rlncConfig.get_TotalFrameCount() - processedFrames;

    // If the total frame count left-over is less than the generation size, we take that
    if (generationSize <= totalFrameCountLeft) {
        return generationSize;
    } else {
        return totalFrameCountLeft;
    }
}

bool RlncDecoder::DecidePacketErrorDroppage(bool isUpdatePacket) {
    auto receptionConfig = rlncConfig.get_receptionRateConfig();

    if (!receptionConfig.get_DropUpdateCommands() && isUpdatePacket) {
        return false;
    }

    float approxPer = receptionConfig.get_PacketErrorRate();
    int32_t fixedPer = (int32_t)(approxPer * 10000.0f);
    if (approxPer > 0.0000001f && approxPer < 0.999999f) {
        int32_t randomValue = randr(0, 10000);
        bool willDropPacket = randomValue < fixedPer;
        if (willDropPacket) {
            if (isUpdatePacket) {
                UartDebug("RLNC_RNG_DROP", 0, 14);
            } else {
                UartDebug("RLNC_RNG_DROP", randomValue, 14);
            }
        } else {
            if (!isUpdatePacket) {
                UartDebug("RLNC_RNG_ACPT", randomValue, 14);
            } else {
                UartDebug("RLNC_RNG_ACPT", 0, 14);
            }
        }
        return willDropPacket;
    }

    return false;
}

void RlncDecoder::ProcessRlncFragment(LORA_MSG_TEMPLATE& message) {
    bool willDropPacketByRng = DecidePacketErrorDroppage(false);
    if (willDropPacketByRng) return;

    uint32_t correlationCode = message.get_CorrelationCode();
    uint32_t maxGenerationSize = rlncConfig.get_GenerationSize() + rlncConfig.get_GenerationRedundancySize();

    // Parse the new generationIndex
    uint32_t tempGenerationIndex = 0;
    uint32_t tempFragmentIndex = 0;
    DecodeRlncSequenceNumber(correlationCode, maxGenerationSize, &tempFragmentIndex, &tempGenerationIndex);

    uint8_t missedGenerations = (uint8_t)tempGenerationIndex - generationIndex;
    if (missedGenerations > 0) {
        UartDebug("RLNC_LAG_GEN", missedGenerations, 12);
        generationSucceeded = false;
        generationIndex = tempGenerationIndex;
        ReserveGenerationStorage();
    }

    if (generationSucceeded) return;

    uint32_t totalFragmentIndex = receivedGenFragments + missedGenFragments;
    if (tempFragmentIndex > totalFragmentIndex) {
        missedGenFragments += tempFragmentIndex - totalFragmentIndex;
        UartDebug("RLNC_LAG_FRAG", missedGenFragments, 13);
    }

    // Fetch the encoding vector length
    auto encodingColCount = GetEncodingVectorLength();
    uint32_t prngSeedState = message.get_rlncEncodedFragment().get_PRngSeedState();
    
    auto frame = message.get_Payload();
    auto frameSize = frame.get_length();

    if (frameSize != rlncConfig.get_FrameSize()) {
        // Bad or illegal configuration
        ThrowDecodingError(DecodingError::FRAME_SIZE_MISMATCH);
    }

    // Insert the encoding vector and encoded frame
    vector<SYMB> augVector;

    // Reproduce the encoding vector
    uint8_t val0 = (uint8_t)(prngSeedState >> 24);
    uint8_t val1 = (uint8_t)(prngSeedState >> 16);
    uint8_t val2 = (uint8_t)(prngSeedState >> 8);
    uint8_t val3 = (uint8_t)(prngSeedState);
    rng.set_State(val0, val1, val2, val3);
    RngGenerateMany(augVector, encodingColCount);

    uint32_t currentPrngSeedState;
    uint8_t cVal0 = (uint8_t)(rng.get_State0());
    uint8_t cVal1 = (uint8_t)(rng.get_State1());
    uint8_t cVal2 = (uint8_t)(rng.get_State2());
    uint8_t cVal3 = (uint8_t)(rng.get_State3());
    currentPrngSeedState = (cVal0 << 24) + (cVal1 << 16) + (cVal2 << 8) + cVal3;

    // Store the augmented part
    for (uint8_t i = 0; i < frameSize; i++) {
        augVector.push_back(frame[i]);
    }

    // Store the augmented matrix row
    bool success = DetermineSuccess(); // Before spoiling the matrix
    uint8_t rowIndex = AddFrameAsMatrixRow(augVector);

    // Debug previous decoding action and any new packet
    uint8_t crc1 = ComputeChecksum(decodingMatrix[0].data(), decodingMatrix[0].size());
    uint8_t crc2 = ComputeChecksum(decodingMatrix[rowIndex].data(), decodingMatrix[0].size());
    DecodingUpdate decodingUpdate;
    decodingUpdate.set_RankProgress(DetermineNextInnovativeRowIndex());
    decodingUpdate.set_ReceivedFragments(receivedGenFragments);
    decodingUpdate.set_MissedGenFragments(missedGenFragments);
    decodingUpdate.set_CurrentGenerationIndex(generationIndex);
    decodingUpdate.set_IsRunning(!terminated);
    decodingUpdate.set_Success(success);
    decodingUpdate.set_UsedPrngSeedState(prngSeedState);
    decodingUpdate.set_CurrentPrngState(currentPrngSeedState);
    decodingUpdate.set_FirstRowCrc8(crc1);
    decodingUpdate.set_LastRowCrc8(crc2);
    decodingUpdate.set_LastRowIndex(rowIndex);

    if (rlncConfig.get_DebugFragmentUart()) {
        // Contains the untouched frame, so send before decoding
        UartSendDecodingUpdate(decodingUpdate, augVector.data(), augVector.size());
    } else {
        UartSendDecodingUpdateWithoutPayload(decodingUpdate);
    }

    // Decoding should not fail when incomplete
    DecodeFragments(lastDecodingResult);

    // Process the results - if any
    if (tempFragmentIndex == encodingColCount - 1 || (receivedGenFragments >= encodingColCount && lastDecodingResult.get_Success())) {
        // Delegate to Flash, UART or LoRa
        SendUartDecodingResult(lastDecodingResult);
        // StoreDecodingResult(result);
    }
}

void RlncDecoder::DecodeFragments(DecodingResult& result) {
    CRITICAL_SECTION_BEGIN();

    // Get the symbols to skip in RREF
    auto augLength = rlncConfig.get_FrameSize();
    ReduceMatrix(augLength);

    CRITICAL_SECTION_END();
}

/**
 * @brief Update the state to move or reset generation
 *
 * @param rlncStateUpdate
 */
void RlncDecoder::UpdateRlncDecodingState(const RlncStateUpdate& rlncStateUpdate) {
    // if (DecidePacketErrorDroppage(true)) return;

    // Skipped or failed generations also need tracking
    // uint32_t newGenerationIndex = rlncStateUpdate.get_GenerationIndex();
    // if (newGenerationIndex - generationIndex > 1 || !generationSucceeded) {
    //     SendUartDecodingResult(lastDecodingResult);
    // }

    // Update state
    // generationIndex = newGenerationIndex;
    // generationSucceeded = false;

    // lfsr->Reset();

    // Prepare for next generation, reset state
    // ReserveGenerationStorage();
}

void RlncDecoder::TerminateRlnc(const RlncTerminationCommand& RlncTerminationCommand) {
    AutoTerminateRlnc();
}

void RlncDecoder::AutoTerminateRlnc() {
    // Reset state
    generationIndex = 0x0;
    rng.set_State(0x00, 0x00, 0x00, 0x00); // Would cause an error
    ClearDecodingMatrix();
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

uint8_t RlncDecoder::AddFrameAsMatrixRow(vector<SYMB>& row) {
    receivedGenFragments++;

    auto innovativeRow = DetermineNextInnovativeRowIndex();
    if (innovativeRow > this->decodingMatrix.size()) {
        ThrowDecodingError(DecodingError::INNO_ROW_EXCEEDS_MATRIX_ROWS);
    }
    if (row.size() > this->decodingMatrix[innovativeRow].size()) {
        ThrowDecodingError(DecodingError::INNO_ROW_EXCEEDS_MATRIX_COLS);
    }
    this->decodingMatrix[innovativeRow].assign(row.begin(), row.end());
    return innovativeRow;
}

uint8_t RlncDecoder::DetermineNextInnovativeRowIndex() {
    // Only the encoding vector columns need checking
    auto encodingVectorLength = GetEncodingVectorLength();

    if (decodingMatrix.size() == 0) {
        ThrowDecodingError(DecodingError::MATRIX_SIZE_0_ADD_ROW);
    }

    for (uint8_t i = 0; i < decodingMatrix.size(); i++) {
        bool currentRowAllZeroes = true;
        for (uint8_t j = 0; j < encodingVectorLength; j++) {
            // As we assume non-RREF any value not zero means rank++
            if (decodingMatrix[i][j] != 0) {
                currentRowAllZeroes = false;
                break;
            }
        }

        if (currentRowAllZeroes) return i;
    }

    // This may not happen because empty rows should have returned lower rank than full rank
    if (receivedGenFragments < encodingVectorLength) {
        ThrowDecodingError(DecodingError::ILLEGAL_RANK_STATE);
    }

    // If no row is all-0 we have full rank - we return the effective generation size (as index)
    return encodingVectorLength - 1;
}

void RlncDecoder::ReduceMatrix(uint8_t augmentedCols) {
    auto totalRowCount = decodingMatrix.size();
    auto totalColCount = decodingMatrix[0].size();

    if (augmentedCols >= totalColCount) {
        ThrowDecodingError(DecodingError::AUGMENTED_COLS_EXCEEDS_TOTAL);
    }

    if (rlncConfig.get_DebugMatrixUart()) {
        DebugSendMatrix();
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
        for (uint8_t tmpRow = 0; tmpRow < pivotRow.value(); tmpRow++) {
            EliminateRow(tmpRow, pivotRow.value(), col, totalColCount);
        }

        // Eliminate Next Rows
        for (uint8_t tmpRow = pivotRow.value(); tmpRow < totalRowCount; tmpRow++) {
            EliminateRow(tmpRow, pivotRow.value(), col, totalColCount);
        }
    }

    if (rlncConfig.get_DebugMatrixUart()) {
        DebugSendMatrix();
    }
}

void RlncDecoder::DebugSendMatrix() {
    // Debug by sending the matrix over UART
    auto colCount = decodingMatrix[0].size();
    auto rowCount = decodingMatrix.size();
    auto totalCount = rowCount * colCount;
    uint8_t serialMatrix[rowCount * colCount];
    for (uint8_t i = 0; i < rowCount; i++) {
        for (uint8_t j = 0; j < colCount; j++) {
            serialMatrix[i * colCount + j] = decodingMatrix[i][j];
        }
    }

    DecodingMatrix matrixSizes;
    matrixSizes.set_Rows(rowCount);
    matrixSizes.set_Cols(colCount);
    UartSendDecodingMatrix(matrixSizes, serialMatrix, totalCount);
}

optional<uint8_t> RlncDecoder::FindPivot(uint8_t startRow, uint8_t col, uint8_t rowCount) {
    if (rowCount == 0) {
        ThrowDecodingError(DecodingError::FIND_PIVOT_ROWCOUNT_0);
    }

    for (uint8_t i = startRow; i < rowCount; i++) {
        if (decodingMatrix[i][col] != galois::nil)
            return i;
    }

    return {};
}

void RlncDecoder::SwitchRows(uint8_t row1, uint8_t row2, uint8_t colCount) {
    if (row1 == row2) return;

    for (int col = 0; col < colCount; col++) {
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

void RlncDecoder::SendUartDecodingResult(DecodingResult& result) {
    uint32_t encVectorLength = GetEncodingVectorLength();
    uint8_t progress = DetermineNextInnovativeRowIndex() + 1;
    uint32_t numberColumn = encVectorLength + 3;  // 4th byte is a fixated column
    uint32_t firstNumber = decodingMatrix[0][numberColumn];
    uint32_t lastRowIndex = encVectorLength - 1;
    uint32_t lastNumber = decodingMatrix[lastRowIndex][numberColumn];

    bool success = DetermineSuccess();
    if (success) {
        generationSucceeded = true;
    }

    result.set_Success(success);
    result.set_MatrixRank(progress);
    result.set_MissedGenFragments(missedGenFragments);
    result.set_ReceivedFragments(receivedGenFragments);
    result.set_CurrentGenerationIndex(generationIndex);
    result.set_FirstDecodedNumber(firstNumber);
    result.set_LastDecodedNumber(lastNumber);
    UartSendDecodingResult(result);

    // Clear the results after sending for better state management
    result.clear();
}

bool RlncDecoder::DetermineSuccess() {
    auto encVectorLength = GetEncodingVectorLength();
    auto generationSize = rlncConfig.get_GenerationSize();
    auto numberColumn = encVectorLength + 3;  // 4th byte is a fixated column
    auto firstNumber = decodingMatrix[0][numberColumn];
    auto lastRowIndex = encVectorLength - 1;
    auto lastNumber = decodingMatrix[lastRowIndex][numberColumn];
    auto correctFirstNumber = generationSize * generationIndex;
    auto correctLastNumber = correctFirstNumber + encVectorLength - 1;

    bool success = firstNumber == correctFirstNumber && lastNumber == (correctLastNumber);

    return success;
}

void RlncDecoder::ThrowDecodingError(DecodingError error) {
    ThrowMcuBreakpoint();
    while (1) {
        UartDebug("RLNC_ERR", error, 8);
        DelayMs(2000);
    }
}

void RlncDecoder::RngGenerateMany(vector<uint8_t>& output, uint16_t count) {
    for (int i = 0; i < count; i++) {
        output.push_back(rng());
    }
}
