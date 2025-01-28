#include "../include/gnome_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

// O(n pow 2)
void gnome_sort(int arr[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i - 1] <= arr[i]) {
            i++;
        } else {
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
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
    gnome_sort(arr, n);
    clock_t end_time = clock();

    double elapsed_time = ((double)(end_time - start_time) * 1000) / CLOCKS_PER_SEC;
    printf(YELLOW "Execution Time: %.2f ms" RESET "\n", elapsed_time);

    free(arr);
    return 0;
}
