#include "../include/radix_sort.h"
#include <stdlib.h>

int key(int x, int i) {
    while (i > 0) {
        x /= 10;
        i--;
    }
    return x % 10;
}

void sort_aux(int arr[], int n, int i) {
    int output[n];
    int count[10] = {0};

    for (int j = 0; j < n; j++)
        count[key(arr[j], i)]++;

    for (int j = 1; j < 10; j++)
        count[j] += count[j - 1];

    for (int j = n - 1; j >= 0; j--) {
        output[count[key(arr[j], i)] - 1] = arr[j];
        count[key(arr[j], i)]--;
    }

    for (int j = 0; j < n; j++)
        arr[j] = output[j];
}

void radix_sort(int arr[], int n, int k) {
    for (int i = 0; i < k; i++)
        sort_aux(arr, n, i);
}
