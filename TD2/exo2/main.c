#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "search.h"
#include "utils.h"

int main(void)
{
    
    int n = 100000;
    int *arr = (int*)malloc(n * sizeof(int));
    
    // test avec array trié
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2; 
    }
    
    
    int target = 50000;
    
    // linear search test
    clock_t start = clock();
    int result_linear = linear_search(arr, n, target);
    clock_t end = clock();
    double time_linear = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    //jump search test
    start = clock();
    int result_jump = jump_search(arr, n, target);
    end = clock();
    double time_jump = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // clock for binary search
    start = clock();
    int result_binary = binary_search(arr, n, target);
    end = clock();
    double time_binary = ((double)(end - start)) / CLOCKS_PER_SEC;
  
    printf("Tableau de taille: %d\n", n);
    printf("Cible: %d\n\n", target);
    
    printf("Linear Search:\n");
    printf("Index: %d, Temps: %.6f secondes\n\n", result_linear, time_linear);
    
    printf("Jump Search:\n");
    printf("Index: %d, Temps: %.6f secondes\n\n", result_jump, time_jump);
    
    printf("Binary Search:\n");
    printf("Index: %d, Temps: %.6f secondes\n\n", result_binary, time_binary);
    
    
    printf(" Test avec tableau non trie \n");
    int unsorted_arr[] = {5, 2, 8, 1, 9};
    int unsorted_size = 5;
    
    int jump_result_unsorted = jump_search(unsorted_arr, unsorted_size, 8);
    int binary_result_unsorted = binary_search(unsorted_arr, unsorted_size, 8);
    
    printf("Jump search sur tableau non trie: %d\n", jump_result_unsorted);
    printf("Binary search sur tableau non trie: %d\n", binary_result_unsorted);
    
   
    return 0;
}
