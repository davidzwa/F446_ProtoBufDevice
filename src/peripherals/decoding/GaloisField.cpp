#include "GaloisField.h"

namespace galois {

GaloisField::GaloisField() : power(0), field_size(0) {
    antiLogLUT = new GFSymbol[1];
    logLUT = new GFSymbol[1];
    invLUT = new GFSymbol[1];
    prim_poly_hash = 0;
}

GaloisField::GaloisField(const int pwr, const unsigned int* primitive_poly) : power(pwr), field_size((1 << power) - 1) {
    antiLogLUT = new GFSymbol[field_size + 1];
    logLUT = new GFSymbol[field_size + 1];

    prim_poly_hash = 0xAAAAAAAA;

    for (unsigned int i = 0; i < power; i++) {
        prim_poly_hash += ((i & 1) == 0) ? ((prim_poly_hash << 7) ^ primitive_poly[i] ^ (prim_poly_hash >> 3)) : (~((prim_poly_hash << 11) ^ primitive_poly[i] ^ (prim_poly_hash >> 5)));
    }

    generate_field(primitive_poly);
}

GaloisField::GaloisField(const GaloisField& gf) {
    power = gf.power;
    field_size = gf.field_size;
    prim_poly_hash = gf.prim_poly_hash;
    antiLogLUT = new GFSymbol[field_size + 1];
    logLUT = new GFSymbol[field_size + 1];

    memcpy(antiLogLUT, gf.antiLogLUT, (field_size + 1) * sizeof(GFSymbol));
    memcpy(logLUT, gf.logLUT, (field_size + 1) * sizeof(GFSymbol));

    // Optimization of 1/VAL
    invLUT = new GFSymbol[(field_size + 1) * 2];
    memcpy(invLUT, gf.invLUT, (field_size + 1) * sizeof(GFSymbol) * 2);
}

GaloisField::~GaloisField() {
    if (antiLogLUT != NULL) delete[] antiLogLUT;
    if (logLUT != NULL) delete[] logLUT;
    if (invLUT != NULL) delete[] invLUT;
}

bool GaloisField::operator==(const GaloisField& gf) {
    return (
        (this->power == gf.power) &&
        (this->prim_poly_hash == gf.prim_poly_hash));
}

GaloisField& GaloisField::operator=(const GaloisField& gf) {
    if (this == &gf)
        return *this;

    if (antiLogLUT != NULL) delete[] antiLogLUT;
    if (logLUT != NULL) delete[] logLUT;

    power = gf.power;
    field_size = gf.field_size;
    prim_poly_hash = gf.prim_poly_hash;

    memcpy(antiLogLUT, gf.antiLogLUT, (field_size + 1) * sizeof(GFSymbol));
    memcpy(logLUT, gf.logLUT, (field_size + 1) * sizeof(GFSymbol));

    // Copy over 1/VAL table
    if (invLUT != NULL) delete[] invLUT;
    invLUT = new GFSymbol[(field_size + 1) * 2];
    memcpy(invLUT, gf.invLUT, (field_size + 1) * sizeof(GFSymbol) * 2);

    return *this;
}

void GaloisField::generate_field(const unsigned int* prim_poly) {
    /*
         Note: It is assumed that the degree of the primitive
               polynomial will be equivelent to the m value as
               in GF(2^m)
      */

    /*
         need to update using stanford method for prim-poly generation.
      */
    int mask = 1;

    antiLogLUT[power] = 0;

    for (unsigned int i = 0; i < power; i++) {
        antiLogLUT[i] = mask;
        logLUT[antiLogLUT[i]] = i;

        if (prim_poly[i] != 0) {
            antiLogLUT[power] ^= mask;
        }

        mask <<= 1;
    }

    logLUT[antiLogLUT[power]] = power;

    mask >>= 1;

    for (unsigned int i = power + 1; i < field_size; i++) {
        if (antiLogLUT[i - 1] >= mask)
            antiLogLUT[i] = antiLogLUT[power] ^ ((antiLogLUT[i - 1] ^ mask) << 1);
        else
            antiLogLUT[i] = antiLogLUT[i - 1] << 1;

        logLUT[antiLogLUT[i]] = i;
    }

    logLUT[0] = GFERROR;
    antiLogLUT[field_size] = 1;

    for (unsigned int i = 0; i < (field_size + 1); i++) {
        invLUT[i] = generateInverseLUT(i);
        invLUT[i + (field_size + 1)] = invLUT[i];
    }

}

GFSymbol GaloisField::fast_modulus(GFSymbol x) {
    while (x >= (int)field_size) {
        x -= (int)field_size;
        x = (x >> power) + (x & (int)field_size);
    }

    return x;
}

GFSymbol GaloisField::generateInverseLUT(const GFSymbol& val) {
    return antiLogLUT[fast_modulus(field_size - logLUT[val])];
}

}  // namespace galois
