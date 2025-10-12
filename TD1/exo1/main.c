#include <stdio.h>
#include <time.h>

#include "fibonnaci.h"

int main(void){
    int DPFib[7];
    for(int i=0;i<=6;i++){
        DPFib[i]=-1;
    }
    clock_t begin = clock();
    int r1=NaiveFibonacci(6);
    printf(" Naive Fibonnaci :%i \n",r1);
    clock_t end = clock();
    double millis = (double)(end -  begin) * 1000.0 / CLOCKS_PER_SEC;
    printf( "Finished in %.2f ms\n", millis );
    clock_t begin2= clock();
    int r2=DPFibonnaci(6,DPFib); 
    printf(" Dynamic Fibonacci : %i \n",r2);
    clock_t end2=clock();
    double millis2 = (double)(end2 -  begin2) * 1000.0 / CLOCKS_PER_SEC;
    printf( "Finished in %.2f ms\n", millis2 );

return 0;
}
