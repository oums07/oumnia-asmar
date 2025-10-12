#include "primes.h"
#include <stdio.h>


int NaiveMethod(int n, int primes[]) {
    int c = 0;

    for (int i = 2; i <= n; i++) {
        int isPrime = 1; 
        for (int j = 2; j*j <= i; j++) { 
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) {
            primes[c] = i;  
            c++;
        }
    }

    return c; 
}

void OptimalMethod(int n){
    bool prime[n+1];
    prime[0]=prime[1]=false;
    for(int k=2;k<n;k++)
       prime[k]=true;
    for(int i=2;i*i<n;i++){
        if(prime[i]){
            for(int j=i*i;j<=n;j+=i){
                prime[j]=false;
            }
        }
    }
    printf("primes up to %i :",n);
    for(int i=0;i<=n;i++){
        if(prime[i]== true)
         printf("%i  ", i);
    }
    printf("\n");
}