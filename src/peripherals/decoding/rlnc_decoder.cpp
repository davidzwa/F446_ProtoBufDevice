#include "rlnc_decoder.h"

// #include <cstdlib>
// #include <iomanip>

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
        // printmatrix(A);
    }
}
