
#include<stdio.h>
#include<omp.h>

static long num_staps = 1000;
double step;
int main(){

int i;
double pi , x ,sum = 0.0;
step=1.0/(double)num_staps ;

{
    double x;

    #pragma omp parallel for reduction(+:sum) private(x,i)
    for (i=0 ; i < num_staps ; ++i){
        x=(double)(i+0.5)*step;
        sum = sum + 4.0/(1.0 + x * x);
    }

}

pi = step * sum;
printf("The value of PI is %f\n",pi);

    return 0;
}
