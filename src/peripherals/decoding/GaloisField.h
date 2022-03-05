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

const GFSymbol nil(0);
const GFSymbol unity(1);

class GaloisField {
   public:
    GaloisField(const int pwr, const unsigned int primitive_poly);

    inline unsigned int size() const {
        return Order;
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
        else {
            return multiply(a, b);
        }
    }

    inline GFSymbol div(const GFSymbol& a, const GFSymbol& b) {
        if ((a == 0) || (b == 0))
            return 0;
        else {
            return divide(a, b);
        }
    }

    inline GFSymbol exp(const GFSymbol& f, const int& exp) {
        if (f == 0) {
            return 0;
        }

        auto fieldTemp = GFSymbol(1);
        for (GFSymbol i = 0; i < exp; i++) {
            fieldTemp = multiply(fieldTemp, f);
        }

        return fieldTemp;
    }

   private:
    void generate_field();
    GFSymbol multiply(GFSymbol a, GFSymbol b);
    GFSymbol divide(GFSymbol a, GFSymbol b);

   private:
    unsigned int power;
    long Order;
    unsigned int prim_poly_hash;
    unsigned int primitivePoly;

    GFSymbol* antiLogLUT;  // aka exponential or anti-log
    GFSymbol* logLUT;      // aka log

    // Generator is a special chosen value to loop over the whole field during multiplication
    const GFSymbol generator = 0x02;
};

}  // namespace galois

#endif
