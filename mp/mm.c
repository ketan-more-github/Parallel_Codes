#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include "omp.h"
#endif
#define N 1000

void mm(double *a, double *b, double *c)
{

    #pragma omp parallel for collapse(2)  default(none) shared(a,b,c) 
     for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            double sum = 0;
            #pragma unroll(32)
            #pragma omp simd 
            for(int k = 0; k < N; k++)
            {
                sum += a[i * N + k] * b[k * N + j]; 
            }
            c[i * N + j] = sum;
        }
    }

}

void print(double *m)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%lf \n", m[i * N + j]);
        }
    }
}

int main()
{

#ifdef _OPENMP
    omp_set_num_threads(8);
#endif

    double *A, *B, *C;

    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    C = (double *)malloc(N * N * sizeof(double));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i * N + j] = 1;
            B[i * N + j] = 2;
        }
        /* code */
    }
    

    mm(A, B, C);

    print(C);
    printf("\n");

    free(A);
    free(B);
    free(C);
    return 0;
}