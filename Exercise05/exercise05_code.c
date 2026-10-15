#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
        #pragma omp task shared(i) firstprivate(n)
        i = fib(n - 1);

        #pragma omp task shared(j) firstprivate(n)
        j = fib(n - 2);

        #pragma omp taskwait
        return i + j;
    }
}

int main() {
    int n = 10, result;
    double tstart = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    double tstop = omp_get_wtime();
    printf("Fibonacci(%d) = %d | Time: %.4f ms\n", n, result, (tstop - tstart) * 1000.0);
    return 0;
}
