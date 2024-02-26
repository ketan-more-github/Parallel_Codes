#include <stdio.h>
#include <omp.h>
#define N 5

int main(int argc, char * argv[])
{
    int i = 10;
    int a[N], b[N], c[N], d[N];
    double sum = 1;
    double sum1 = 1;
    for (i = 0; i < N; ++i)
    {
        a[i] = i * 2;
        b[i] = i + 20;
    }

    i = 1;

    omp_set_num_threads(2);

    #pragma omp parallel shared(a, b, c, d , sum1 , sum)
        {
            #pragma omp sections 
                {
                    #pragma omp section
                        for (i = 0; i < N; ++i)
                         {

                           c[i] = a[i] + b[i];
                            sum = sum + c[i];
                            printf("Section 1 working thred : %d | %d + %d = %d \n", omp_get_thread_num(), a[i], b[i], c[i]);
                        }

                    #pragma omp section
                        for (i = 0; i < N; ++i)
                        {
                            d[i] = a[i] * b[i];
                            sum1 = sum1 + d[i];
                            printf("Section 2 working thred : %d | %d * %d = %d \n", omp_get_thread_num() , a[i], b[i], d[i]  );
                        }
                }
            printf("sun of addition outside = %lf\n", sum);
            printf("sum of multiplication outside = %lf\n", sum1);
        
        }
        
      printf("\n");
      printf("sun of addition outside = %lf\n" , sum);
      printf("sum of multiplication outside = %lf\n" , sum1);

    return 0;
}