#include "../include/utils.h"
#include <stdlib.h>
#include <time.h>

void generate_random_array(int arr[], int n, int max_value) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_value;
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

double measure_time(void (*sort_function)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sort_function(arr, n);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}
