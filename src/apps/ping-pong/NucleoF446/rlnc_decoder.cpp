#include "rlnc_decoder.h"

// State

RlncDecoder::RlncDecoder() {
    lfsr = new LFSR(LFSR_DEFAULT_SEED);
    terminated = true;
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
}

void RlncDecoder::PrepareFragmentStorage() {
    generationFrames.clear();
    // Quite conservative (2 overhead) - does not assume any dependent vectors arrive
    generationFrames.reserve(rlncDecodingConfig.get_GenerationSize() + 2);
}

void RlncDecoder::ProcessRlncFragment(SYMB* payload, uint8_t payloadLength) {
    // Process the fragment
    RlncFrame frame(payload, payloadLength);
    
    // Fetch the encoding vector length
    auto generationSize = rlncDecodingConfig.get_GenerationSize();

    // Generate the encoding vector
    SYMB encodingVector[(uint8_t)generationSize];
    lfsr->GenerateMany(encodingVector, generationSize);

    // Combine the two into RlncFrame
    frame.SetEncodingVector(encodingVector, generationSize);

    // Store the frame in safe memory
    generationFrames.push_back(frame);

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
    PrepareFragmentStorage();
}

void RlncDecoder::TerminateRlnc(RlncTerminationCommand& RlncTerminationCommand) {
    // Reduce memory usage
    generationFrames.clear();
    generationIndex = 0;

    // Debugging flag for tracking the state
    terminated = true;
}

RlncDecodingResult RlncDecoder::DecodeFragments() {
    RlncDecodingResult result;

    // Create augmented matrix from frame and enc vector
    // generationFrames.size() * (size(frame) + size(enc))
    // GSymbol[][]

    // RREF the augmented matrix

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

/**
 * @brief Get the Next LFSR sample
 *
 * @return uint8_t pseudo-random value
 */
SYMB RlncDecoder::GetNextLFSRState() {
    return lfsr->Generate();
}
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

// Tested with this debug statement
// UartDebug("GF calc", (element1 * element2).poly(), 8);

// float A[3][4] = {{5, -6, -7, 7},
//                  {3, -2, 5, -17},
//                  {2, 4, -3, 29}};  // answer should be {2, 4, -3}
// RowReduce(A);

// https://rosettacode.org/wiki/Reduced_row_echelon_form
// https://stackoverflow.com/questions/31756413/solving-a-simple-matrix-in-row-reduced-form-in-c
void RowReduce(float A[][4]) {
    const int nrows = 3;  // number of rows
    const int ncols = 4;  // number of columns

    int lead = 0;

    while (lead < nrows) {
        float d, m;

        for (int r = 0; r < nrows; r++) {  // for each row ...
            /* calculate divisor and multiplier */
            d = A[lead][lead];
            m = A[r][lead] / A[lead][lead];

            for (int c = 0; c < ncols; c++) {  // for each column ...
                if (r == lead)
                    A[r][c] /= d;  // make pivot = 1
                else
                    A[r][c] -= A[lead][c] * m;  // make other = 0
            }
        }

        lead++;
    }
}
