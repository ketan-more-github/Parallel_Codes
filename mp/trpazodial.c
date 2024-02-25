#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 1000// number of trapazium
#define PI 3.14159265358
#ifdef _OPENMP
#include <omp.h>
#endif

double func(double x)
{
    return (sin(x) / (2 * x * x * x));
}

double trpazodial_rule(double a, double b, double *result)
{
    double h, total, x;
    int rank = omp_get_thread_num();
    int size = omp_get_num_threads();
    int local_n;
    double local_a, local_b;

    h = (b - a) / 2;
    local_n = N / size;
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    total = (func(local_a) + func(local_b)) / 2.0;

    for (int i = 1; i < N - 1; i++)
    {
        x = local_a + i * h;
        total += func(x);
    }

    total = total * h;
    return total;
}

int main()
{

#ifdef _OPENMP
    omp_set_num_threads(8);
#endif
    double a, b, result;
    a = 1.0; // left boundary
    b = PI;  // right boundary
    result = 0.0;
#pragma omp parallel reduction(+:result)
    {
        double my_result = 0.0;
        my_result = trpazodial_rule(a, b, &result);
        result += my_result;
    }

    printf("\n the area under the curve (1+sin(x)) between 0 to PI is equal to %lf \n\n ", result);

    return 0;
}