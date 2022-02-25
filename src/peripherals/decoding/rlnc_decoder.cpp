#include "rlnc_decoder.h"

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
