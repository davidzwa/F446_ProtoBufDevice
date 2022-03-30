#include "rlnc_decoder.h"

#include "Crc8.h"
#include "cli.h"
#include "delay.h"
#include "utilities.h"

unsigned int prim_poly = 0x11D;
galois::GaloisField gf(8, prim_poly);

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

    // Apply to LFSR
    lfsr->Seed = rlncInitConfig.get_LfsrSeed();
    lfsr->Reset();

    // Prepare storage for the configured generation
    ReserveGenerationStorage();
}

void RlncDecoder::ReserveGenerationStorage() {
    ClearDecodingMatrix();
    receivedFragments = 0;

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

    auto approxPer = receptionConfig.get_PacketErrorRate();
    auto fixedPer = approxPer * 10000;
    if (approxPer > 0.0000001f && approxPer < 0.999999f) {
        auto randomValue = randr(0, 10000);
        auto willDropPacket = randomValue < fixedPer;
        if (willDropPacket) {
            UartDebug("RLNC_RNG", randomValue, 8);
        }
        return willDropPacket;
    }

    return false;
}

void RlncDecoder::ProcessRlncFragment(LORA_MSG_TEMPLATE& message) {
    if (generationSucceeded) return;
   
    bool willDropPacketByRng = DecidePacketErrorDroppage(true);
    if (willDropPacketByRng) return;

    // Fetch the encoding vector length
    auto encodingColCount = GetEncodingVectorLength();
    auto lfsrResetState = message.get_rlncEncodedFragment().get_LfsrState();
    auto frame = message.get_Payload();
    auto frameSize = frame.get_length();

    if (frameSize != rlncConfig.get_FrameSize()) {
        // Bad or illegal configuration
        ThrowDecodingError(DecodingError::FRAME_SIZE_MISMATCH);
        throw "Illegal frame size";
    }

    // Insert the encoding vector and encoded frame
    vector<SYMB> augVector;

    // Reproduce the encoding vector
    lfsr->State = lfsrResetState;
    lfsr->GenerateMany(augVector, encodingColCount);

    // Store the augmented part
    for (uint8_t i = 0; i < frameSize; i++) {
        augVector.push_back(frame[i]);
    }

    // Store the augmented matrix row
    auto rowIndex = AddFrameAsMatrixRow(augVector);

    // Debug previous decoding action and any new packet
    uint8_t crc1 = ComputeChecksum(decodingMatrix[0].data(), decodingMatrix[0].size());
    uint8_t crc2 = ComputeChecksum(decodingMatrix[rowIndex].data(), decodingMatrix[0].size());
    DecodingUpdate decodingUpdate;
    decodingUpdate.set_RankProgress(DetermineNextInnovativeRowIndex());
    decodingUpdate.set_ReceivedFragments(receivedFragments);
    decodingUpdate.set_CurrentGenerationIndex(generationIndex);
    decodingUpdate.set_IsRunning(!terminated);
    decodingUpdate.set_UsedLfsrState(lfsrResetState);
    decodingUpdate.set_CurrentLfsrState(lfsr->State);
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
    DecodingResult result;
    DecodeFragments(result);

    // Process the results - if any
    if (receivedFragments >= encodingColCount) {
        // Enough packets have arrived to attempt decoding with high probability
        // DecodeFragments(result);

        // Verify decoding success and do packet integrity check
        auto encVectorLength = GetEncodingVectorLength();
        uint8_t progress = DetermineNextInnovativeRowIndex() + 1;
        auto numberColumn = encVectorLength + 3;  // 4th byte is a fixated column
        auto firstNumber = decodingMatrix[0][numberColumn];
        auto lastRowIndex = encVectorLength - 1;
        auto lastNumber = decodingMatrix[lastRowIndex][numberColumn];

        auto generationSize = rlncConfig.get_GenerationSize();
        auto correctFirstNumber = generationSize * generationIndex;
        auto correctLastNumber = correctFirstNumber + encVectorLength - 1;

        bool success = firstNumber == correctFirstNumber && lastNumber == (correctLastNumber);
        if (success) {
            generationSucceeded = true;
        }

        result.set_Success(success);
        result.set_MatrixRank(progress);
        result.set_FirstDecodedNumber(firstNumber);
        result.set_LastDecodedNumber(lastNumber);
        UartSendDecodingResult(result);

        // Delegate to Flash, UART or LoRa
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
    if (DecidePacketErrorDroppage(true)) return;

    // Update state
    generationIndex = rlncStateUpdate.get_GenerationIndex();
    generationSucceeded = false;

    // TODO no decoding config update?

    // Prepare for next generation, reset state
    ReserveGenerationStorage();
}

void RlncDecoder::TerminateRlnc(const RlncTerminationCommand& RlncTerminationCommand) {
    AutoTerminateRlnc();
}

void RlncDecoder::AutoTerminateRlnc() {
    // Reset state
    generationIndex = 0x0;
    lfsr->Reset();
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
    receivedFragments++;

    auto innovativeRow = DetermineNextInnovativeRowIndex();
    if (innovativeRow > this->decodingMatrix.size()) {
        ThrowDecodingError(DecodingError::INNO_ROW_EXCEEDS_MATRIX_ROWS);
        throw "Innovative row exceeds matrix allocated rows";
    }
    if (row.size() > this->decodingMatrix[innovativeRow].size()) {
        ThrowDecodingError(DecodingError::INNO_ROW_EXCEEDS_MATRIX_COLS);
        throw "Innovative row exceeds matrix allocated columns";
    }
    // UartDebug("INSERT_ROW", innovativeRow, 11);
    this->decodingMatrix[innovativeRow].assign(row.begin(), row.end());
    return innovativeRow;
}

uint8_t RlncDecoder::DetermineNextInnovativeRowIndex() {
    // Only the encoding vector columns need checking
    auto encodingVectorLength = GetEncodingVectorLength();

    if (decodingMatrix.size() == 0) {
        ThrowDecodingError(DecodingError::MATRIX_SIZE_0_ADD_ROW);
        throw "Matrix not pre-allocated (size 0)";
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

    if (receivedFragments < encodingVectorLength) {
        ThrowDecodingError(DecodingError::ILLEGAL_RANK_STATE);
        throw "Reached full-rank when insufficient packets were received";
    }

    // If no row is all-0 we have full rank - we return the effective generation size
    return encodingVectorLength - 1;
}

void RlncDecoder::ReduceMatrix(uint8_t augmentedCols) {
    auto totalRowCount = decodingMatrix.size();
    auto totalColCount = decodingMatrix[0].size();

    if (augmentedCols >= totalColCount) {
        ThrowDecodingError(DecodingError::AUGMENTED_COLS_EXCEEDS_TOTAL);
        throw "Bad matrix augmentation size";
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
        throw "Illegal rowcount given";
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

void RlncDecoder::ThrowDecodingError(DecodingError error) {
    while (1) {
        UartDebug("RLNC_ERR", error, 8);
        DelayMs(2000);
    }

    throw "Decoding Error catch";
}
