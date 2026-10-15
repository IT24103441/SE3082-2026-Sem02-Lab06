#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define STRIP_SIZE 256  // Aligned with typical SIMD / block widths

int main() {
    double *A = (double*)malloc(N * sizeof(double));
    double *B = (double*)malloc(N * sizeof(double));
    double *C = (double*)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = 1.5;
        B[i] = 2.0;
    }

    double tstart = omp_get_wtime();

    // Strip mining technique
    #pragma omp parallel for
    for (int ii = 0; ii < N; ii += STRIP_SIZE) {
        int limit = (ii + STRIP_SIZE < N) ? (ii + STRIP_SIZE) : N;
        for (int i = ii; i < limit; i++) {
            C[i] = A[i] * B[i];
        }
    }

    double tstop = omp_get_wtime();
    printf("Array multiplication completed. Time: %.4f ms\n", (tstop - tstart) * 1000.0);

    free(A); free(B); free(C);
    return 0;
}
