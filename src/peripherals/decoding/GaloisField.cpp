#include "GaloisField.h"

namespace galois {

GaloisField::GaloisField(const int pwr, const unsigned int primitivePoly) {
    power = pwr;
    Order = (1 << power);
    antiLogLUT = new GFSymbol[Order](); // () initializes them to 0
    logLUT = new GFSymbol[Order]();
    this->primitivePoly = primitivePoly;

    generate_field();
}

void GaloisField::generate_field() {
    GFSymbol val = 0x01;

    // i needs to have bitness of Order
    for (uint16_t i = 0; i < Order; i++) {
        antiLogLUT[i] = val;
        if (i < Order - 1) logLUT[val] = (GFSymbol)i;

        val = multiply(generator, val);
    }
}

GFSymbol GaloisField::multiply(GFSymbol a, GFSymbol b) {
    int result = 0;
    int aa = a;
    int bb = b;
    while (bb != 0) {
        if ((bb & 1) != 0) result ^= aa;

        uint8_t highestBit = (uint8_t)(aa & 0x80);
        aa <<= 1;
        if (highestBit != 0) aa ^= primitivePoly & 0xFF;

        bb >>= 1;
    }

    return result;
}

GFSymbol GaloisField::divide(GFSymbol a, GFSymbol b) {
    auto fieldTempValue = (GFSymbol) ((Order - 1 + logLUT[a] - logLUT[b]) % (Order - 1));
    fieldTempValue = antiLogLUT[fieldTempValue];
    return fieldTempValue;
}

}  // namespace galois
