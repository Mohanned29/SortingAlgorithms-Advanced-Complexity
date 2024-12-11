#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/bubble_sort.h"
#include "../include/gnome_sort.h"
#include "../include/radix_sort.h"
#include "../include/quick_sort.h"
#include "../include/heap_sort.h"
#include "../include/utils.h"

#define MAX_SIZE 10000
#define MAX_VALUE 1000
#define NUM_TESTS 5

int main() {
    int sizes[] = {100, 1000, 5000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int arr[MAX_SIZE];
        double total_times[5] = {0};

        printf("Array size: %d\n", n);

        for (int test = 0; test < NUM_TESTS; test++) {
            generate_random_array(arr, n, MAX_VALUE);

            int arr_copy[MAX_SIZE];
            for (int j = 0; j < n; j++) arr_copy[j] = arr[j];

            total_times[0] += measure_time(bubble_sort, arr_copy, n);
            for (int j = 0; j < n; j++) arr_copy[j] = arr[j];

            total_times[1] += measure_time(bubble_sort_optimized, arr_copy, n);
            for (int j = 0; j < n; j++) arr_copy[j] = arr[j];

            total_times[2] += measure_time(gnome_sort, arr_copy, n);
            for (int j = 0; j < n; j++) arr_copy[j] = arr[j];

            total_times[3] += measure_time(quick_sort, arr_copy, n);
            for (int j = 0; j < n; j++) arr_copy[j] = arr[j];

            total_times[4] += measure_time(heap_sort, arr_copy, n);
        }

        printf("Average times over %d tests:\n", NUM_TESTS);
        printf("Bubble Sort: %.6f seconds\n", total_times[0] / NUM_TESTS);
        printf("Optimized Bubble Sort: %.6f seconds\n", total_times[1] / NUM_TESTS);
        printf("Gnome Sort: %.6f seconds\n", total_times[2] / NUM_TESTS);
        printf("Quick Sort: %.6f seconds\n", total_times[3] / NUM_TESTS);
        printf("Heap Sort: %.6f seconds\n", total_times[4] / NUM_TESTS);

        printf("\n");
    }

    return 0;
}
