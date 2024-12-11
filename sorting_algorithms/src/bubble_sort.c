#include "../include/bubble_sort.h"

void bubble_sort(int arr[], int n) {
    int change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                change = 1;
            }
        }
    }
}

void bubble_sort_optimized(int arr[], int n) {
    int m = n - 1;
    int change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < m; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                change = 1;
            }
        }
        m--;
    }
}
