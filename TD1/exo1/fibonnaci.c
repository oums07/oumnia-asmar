#include "fibonnaci.h"
int NaiveFibonacci(int n){
    if (n==1 || n==0) {
           return n;
    }
    else {
        return NaiveFibonacci(n-1)+NaiveFibonacci(n-2);
    }
}
int DPFibonnaci(int n, int DPFib[]){
    if (n <=1) {
        return n;
    }
    if (DPFib[n]!= -1)
     return DPFib[n];

    DPFib[n]=DPFibonnaci(n-1, DPFib)+DPFibonnaci(n-2, DPFib);
    return DPFib[n];

}
