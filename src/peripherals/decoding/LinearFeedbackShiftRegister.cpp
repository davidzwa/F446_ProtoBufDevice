
#include "LinearFeedbackShiftRegister.h"

#include "utilities.h"

using namespace std;

LFSR::LFSR(uint8_t seed) {
    Seed = seed;
    this->Reset();
}

/**
 * @brief Reset the LFSR including a new seed as starting point
 * 
 * @param seed 
 */
void LFSR::ResetNewSeed(uint8_t seed) {
    this->Seed = seed;
    this->Reset();
}

void LFSR::Reset() {
    this->State = Seed;
    this->GeneratedValuesCount = 0;
}

void LFSR::GenerateMany(vector<uint8_t>& output, uint16_t count) {
    for (int i = 0; i < count; i++) {
        output.push_back(this->Generate());
    }
}

uint8_t LFSR::Generate() {
    if (GeneratedValuesCount > 255){
        ThrowMcuBreakpoint();
    }

    /* Must be 8-bit to allow bit<<7 later in the code */
    /* taps: 8 4 3 1; feedback polynomial: x^8 + x^4 + x^3 + x^1 + 1 */
    // var p = new [] {0, 2, 3, 7}; // 4 entries for GF 2^8
    // 8 6 5 1
    // uint8_t p[] = {0, 1, 2, 7};
    // Bit = (uint8_t)((State >> p[0]) ^ (State >> p[1]) ^ (State >> p[2]) ^ (State >> p[3])); /* & 1u */
    Bit = (uint8_t)((State >> 0) ^ (State >> 1) ^ (State >> 2) ^ (State >> 7)); /* & 1u */
    State = (uint8_t)((State >> 1) | (Bit << (int)(Taps - 1)));                 // Shift the output and cap off

    GeneratedValuesCount++;
    return State;
}
