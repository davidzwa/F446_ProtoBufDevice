/*
  *********************************************************************
  *                                                                   *
  *        Galois Field Arithmetic Library (version 0.0.1)            *
  *                                                                   *
  * Class: Galois Field                                               *
  * Author: Arash Partow - 2000                                       *
  * URL: http://www.partow.net/projects/galois/index.html             *
  *                                                                   *
  * Copyright Notice:                                                 *
  * Free use of this library is permitted under the guidelines and    *
  * in accordance with the most current version of the Common Public  *
  * License.                                                          *
  * http://www.opensource.org/licenses/cpl.php                        *
  *                                                                   *
  *********************************************************************
*/

#ifndef INCLUDE_GALOISFIELD_H
#define INCLUDE_GALOISFIELD_H

#include <stdint.h>
#include <string.h>
#include <vector>

namespace galois {

typedef uint8_t GFSymbol;
const GFSymbol GFERROR = -1;

class GaloisField {
   public:
    GaloisField();
    GaloisField(const int pwr, const unsigned int* primitive_poly);
    GaloisField(const GaloisField& gf);
    ~GaloisField();
    GFSymbol* invLUT;  // multiplicative inverse (pivoting)

    GaloisField& operator=(const GaloisField& gf);
    bool operator==(const GaloisField& gf);

    inline GFSymbol index(const GFSymbol value) const {
        return logLUT[value];
    }

    inline GFSymbol alpha(const GFSymbol value) const {
        return antiLogLUT[value];
    }

    inline unsigned int size() const {
        return field_size;
    }

    inline unsigned int pwr() const {
        return power;
    }

    inline GFSymbol add(const GFSymbol& a, const GFSymbol& b) {
        return (a ^ b);
    }

    inline GFSymbol sub(const GFSymbol& a, const GFSymbol& b) {
        return (a ^ b);
    }

    inline GFSymbol mul(const GFSymbol& a, const GFSymbol& b) {
        if ((a == 0) || (b == 0))
            return 0;
        else
            return antiLogLUT[fast_modulus(logLUT[a] + logLUT[b])];
    }

    inline GFSymbol div(const GFSymbol& a, const GFSymbol& b) {
        if ((a == 0) || (b == 0))
            return 0;
        else
            return antiLogLUT[fast_modulus(logLUT[a] - logLUT[b] + field_size)];
    }

    inline GFSymbol exp(const GFSymbol& a, const int& n) {
        if (a != 0) {
            if (n < 0) {
                int b = n;
                while (b < 0) b += field_size;  // b could be negative
                if (b == 0)
                    return 1;
                return antiLogLUT[fast_modulus(logLUT[a] * b)];
            } else if (n == 0)
                return 1;
            else
                return antiLogLUT[fast_modulus(logLUT[a] * n)];
        } else
            return 0;
    }

    inline GFSymbol inverse(const GFSymbol& val) {
        return invLUT[val];
    }

   private:
    void generate_field(const unsigned int* prim_poly);
    GFSymbol fast_modulus(GFSymbol x);
    GFSymbol generateInverseLUT(const GFSymbol& val);

   private:
    unsigned int power;
    unsigned int field_size;
    unsigned int prim_poly_hash;
    GFSymbol* antiLogLUT;     // aka exponential or anti-log
    GFSymbol* logLUT;     // aka log
    
};

}  // namespace galois

#endif
