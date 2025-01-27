#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/bubble_sort.h"
#include "../include/gnome_sort.h"
#include "../include/radix_sort.h"
#include "../include/quick_sort.h"
#include "../include/heap_sort.h"
#include "../include/counting_sort.h"
#include "../include/utils.h"


#define MAX_SIZE 1000000
#define MAX_VALUE 1000
#define NUM_TESTS 5

typedef void (*SortFunction)(int[], int);

typedef struct {
    const char* name;
    SortFunction function;
} SortAlgorithm;

void run_sorting_benchmark(const SortAlgorithm algorithms[], int num_algorithms, 
                         const int sizes[], int num_sizes) {
    int* arr = (int*)malloc(MAX_SIZE * sizeof(int));
    int* arr_copy = (int*)malloc(MAX_SIZE * sizeof(int));
    
    if (!arr || !arr_copy) {
        fprintf(stderr, "Memory allocation failed\n");
        free(arr);
        free(arr_copy);
        return;
    }

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        double* total_times = (double*)calloc(num_algorithms, sizeof(double));
        
        if (!total_times) {
            fprintf(stderr, "Memory allocation failed for times array\n");
            continue;
        }

        printf("\nArray size: %d\n", n);
        printf("----------------------------------------\n");

        for (int test = 0; test < NUM_TESTS; test++) {
            generate_random_array(arr, n, MAX_VALUE);

            for (int algo = 0; algo < num_algorithms; algo++) {
                for (int j = 0; j < n; j++) {
                    arr_copy[j] = arr[j];
                }

                total_times[algo] += measure_time(algorithms[algo].function, arr_copy, n);
            }
        }

        printf("Average times over %d tests:\n", NUM_TESTS);
        for (int algo = 0; algo < num_algorithms; algo++) {
            printf("%-20s: %.6f seconds\n", 
                   algorithms[algo].name, 
                   total_times[algo] / NUM_TESTS);
        }
        printf("\n");

        free(total_times);
    }

    free(arr);
    free(arr_copy);
}

int main() {
    const SortAlgorithm algorithms[] = {
        {"Bubble Sort", bubble_sort},
        {"Optimized Bubble", bubble_sort_optimized},
        {"Gnome Sort", gnome_sort},
        {"Quick Sort", quick_sort},
        {"Heap Sort", heap_sort},
        {"Counting Sort", counting_sort},
        {"Radix Sort", radix_sort}
    };
    const int num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

    const int sizes[] = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Sorting Algorithm Benchmark\n");
    printf("=============================\n");
    
    run_sorting_benchmark(algorithms, num_algorithms, sizes, num_sizes);

    return 0;
}