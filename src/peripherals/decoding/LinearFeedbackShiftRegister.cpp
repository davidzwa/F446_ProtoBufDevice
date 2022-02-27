
#include "LinearFeedbackShiftRegister.h"

LFSR::LFSR() {
}

void LFSR::Reset() {
    this->State = Seed;
    this->GeneratedValuesCount = 0;
}

uint8_t LFSR::Generate() {
    if (GeneratedValuesCount > 255)
        return 0x00;

    /* Must be 16-bit to allow bit<<15 later in the code */
    /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
    // var A = new [] {0, 2, 3, 5}; // 17-bit (degree 16) with 4 entries
    // Bit = (ushort)((State >> A[0]) ^ (State >> A[1]) ^ (State >> A[2]) ^ (State >> A[3])) /* & 1u */;

    /* Must be 8-bit to allow bit<<7 later in the code */
    /* taps: 8 4 3 1; feedback polynomial: x^8 + x^4 + x^3 + x^1 + 1 */
    // var p = new [] {0, 2, 3, 7}; // 4 entries for GF 2^8
    // 8 6 5 1
    uint8_t p[] = {0, 1, 2, 7};
    Bit = (uint8_t)((State >> p[0]) ^ (State >> p[1]) ^ (State >> p[2]) ^ (State >> p[3])); /* & 1u */
    State = (uint8_t)((State >> 1) | (Bit << (int)(Taps - 1)));                             // Shift the output and cap off

    GeneratedValuesCount++;
    return State;
}