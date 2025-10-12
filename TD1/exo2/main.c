#include <stdio.h>
#include <time.h>
#include "primes.h"
int main() {
    int n = 5;
    int primes[5]; 
    clock_t begin,end;
    begin=clock();
    int count = NaiveMethod(n, primes);
    end=clock();
    printf("Primes up to %d: ", n);
    for (int i = 0; i < count; i++) {
        printf("%d ", primes[i]);
    }
    printf("\n");
    double millis = (double)(end -  begin) * 1000.0 / CLOCKS_PER_SEC;
    printf( "Finished in %.2f ms\n", millis );

    clock_t begin2,end2;
    begin2=clock();
    OptimalMethod(n);
    end2=clock();
    double millis2 = (double)(end -  begin) * 1000.0 / CLOCKS_PER_SEC;
    printf( "Finished in %.2f ms\n", millis2 );
    return 0;

}
