#include "../include/quick_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

static void quick_sort_recursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int n) {
    quick_sort_recursive(arr, 0, n - 1);
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
    quick_sort(arr, n);
    clock_t end_time = clock();

    double elapsed_time = ((double)(end_time - start_time) * 1000) / CLOCKS_PER_SEC;
    printf(YELLOW "Execution Time: %.2f ms" RESET "\n", elapsed_time);

    free(arr);
    return 0;
}
