#include <stdio.h>
#include <omp.h>

#define N 100

int main() {
    int i;
    int a[N], b[N], c[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }

    // Compute sum of arrays
    #pragma omp target map(to:a, b) map(from:c)
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Print result
    printf("Result:\n");
    for (i = 0; i < N; i++) {
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }

    return 0;
}
