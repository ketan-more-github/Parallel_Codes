#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include "omp.h"
#endif
#define N 2000
void mm(double *a, double *b, double *c)
{
     #pragma omp target teams distribute parallel for collapse(2)  default(none) shared(a,b,c)                                    
    //  #pragma omp target map(to:a, b) map(from:c)
    //  #pragma parallel for collapse(2)  default(none) shared(a,b,c) 
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



// #include <stdio.h>
// #include <omp.h>

// #define N 500
// #define M 500

// int main() {
//     int i, j;
//     int A[N][M], x[M], y[N];

//     // Initialize matrix A and vector x
//     for (i = 0; i < N; i++) {
//         for (j = 0; j < M; j++) {
//             A[i][j] = i + j;
//         }
//         x[i] = i;
//     }

//     // Compute matrix-vector multiplication
//     #pragma omp target map(to:A, x) map(from:y)
//     #pragma omp parallel for
//     for (i = 0; i < N; i++) {
//         y[i] = 0;
//         for (j = 0; j < M; j++) {
//             y[i] += A[i][j] * x[j];
//         }
//     }

//     // Print result vector y
//     printf("Result vector y:\n");
//     for (i = 0; i < N; i++) {
//         printf("%d ", y[i]);
//     }
//     printf("\n");

//     return 0;
// }
