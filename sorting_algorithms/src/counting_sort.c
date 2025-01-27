#include "../include/counting_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

void counting_sort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int* count = (int*)calloc(max + 1, sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) count[arr[i]]++;
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];

    free(count);
    free(output);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf(YELLOW "Error: Memory allocation failed!" RESET "\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    clock_t start_time = clock();
    counting_sort(arr, n);
    clock_t end_time = clock();

    double elapsed_time = ((double)(end_time - start_time) * 1000) / CLOCKS_PER_SEC;
    printf(YELLOW "Execution Time: %.2f ms" RESET "\n", elapsed_time);

    free(arr);
    return 0;
}
