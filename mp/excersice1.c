// This exercise is simple; writing an application that calculates for each array element the square of their index and stores it as the 
//element value. Of course, these calculations must be done in parallel.
// a[0] =  0
// a[1] =  1
// a[2] =  4
// a[3] =  9
// a[4] = 16
// a[5] = 25
// a[6] = 36
// a[7] = 49
// a[8] = 64
// a[9] = 81

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 10

int main(){

int a[N] ;
#pragma omp parallel for num_threads(5)
for (int i = 0; i < N; i++)
{
    a[i] = i*i;
    printf("a[%d] = %d\n" , i , a[i]);
}


return 0;

}