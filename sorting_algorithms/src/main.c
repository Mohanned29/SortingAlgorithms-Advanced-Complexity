#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "../include/bubble_sort.h"
#include "../include/gnome_sort.h"
#include "../include/radix_sort.h"
#include "../include/quick_sort.h"
#include "../include/heap_sort.h"
#include "../include/counting_sort.h"
#include "../include/utils.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

#define MAX_VALUE 100
#define DELAY_MILLISECONDS 100

void clear_screen() {
    system("cls");
}

void create_delay() {
    Sleep(DELAY_MILLISECONDS);
}

void print_array_colored(int arr[], int n, int highlighted_idx1, int highlighted_idx2) {
    printf("\n%s[", CYAN);
    for (int i = 0; i < n; i++) {
        if (i == highlighted_idx1 || i == highlighted_idx2) {
            printf("%s%d%s", RED, arr[i], CYAN);
        } else {
            printf("%d", arr[i]);
        }
        
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]%s\n", RESET);
}

void bubble_sort_visual(int arr[], int n) {
    int change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < n - 1; i++) {
            clear_screen();
            printf("%sBubble Sort - Comparing elements %d and %d%s\n", YELLOW, arr[i], arr[i + 1], RESET);
            print_array_colored(arr, n, i, i + 1);
            create_delay();
            
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                change = 1;
            }
        }
    }
    clear_screen();
    printf("%sBubble Sort - Final Result:%s\n", GREEN, RESET);
    print_array_colored(arr, n, -1, -1);
}

void gnome_sort_visual(int arr[], int n) {
    int i = 0;
    while (i < n) {
        clear_screen();
        printf("%sGnome Sort - Checking position %d%s\n", YELLOW, i, RESET);
        print_array_colored(arr, n, i, i > 0 ? i - 1 : -1);
        create_delay();

        if (i == 0 || arr[i - 1] <= arr[i]) {
            i++;
        } else {
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
    clear_screen();
    printf("%sGnome Sort - Final Result:%s\n", GREEN, RESET);
    print_array_colored(arr, n, -1, -1);
}

void heapify_visual(int arr[], int n, int i, int total_size) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    clear_screen();
    printf("%sHeap Sort - Heapifying around index %d%s\n", YELLOW, i, RESET);
    print_array_colored(arr, total_size, left < n ? left : -1, right < n ? right : -1);
    create_delay();

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        heapify_visual(arr, n, largest, total_size);
    }
}

void heap_sort_visual(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_visual(arr, n, i, n);

    for (int i = n - 1; i > 0; i--) {
        clear_screen();
        printf("%sHeap Sort - Extracting maximum%s\n", YELLOW, RESET);
        print_array_colored(arr, n, 0, i);
        create_delay();

        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify_visual(arr, i, 0, n);
    }
    
    clear_screen();
    printf("%sHeap Sort - Final Result:%s\n", GREEN, RESET);
    print_array_colored(arr, n, -1, -1);
}

void quick_sort_visual_recursive(int arr[], int low, int high, int n) {
    if (low < high) {
        clear_screen();
        printf("%sQuick Sort - Partitioning around pivot%s\n", YELLOW, RESET);
        print_array_colored(arr, n, low, high);
        create_delay();
        
        int pi = partition(arr, low, high);
        quick_sort_visual_recursive(arr, low, pi, n);
        quick_sort_visual_recursive(arr, pi + 1, high, n);
    }
}

void quick_sort_visual(int arr[], int n) {
    quick_sort_visual_recursive(arr, 0, n - 1, n);
    clear_screen();
    printf("%sQuick Sort - Final Result:%s\n", GREEN, RESET);
    print_array_colored(arr, n, -1, -1);
}

void counting_sort_visual(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int* count = (int*)calloc(max + 1, sizeof(int));
    if (count == NULL) return;

    for (int i = 0; i < n; i++) {
        clear_screen();
        printf("%sCounting Sort - Counting frequency of %d%s\n", YELLOW, arr[i], RESET);
        print_array_colored(arr, n, i, -1);
        create_delay();
        count[arr[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    int* output = (int*)malloc(n * sizeof(int));
    if (output == NULL) {
        free(count);
        return;
    }

    for (int i = n - 1; i >= 0; i--) {
        clear_screen();
        printf("%sCounting Sort - Placing element %d in correct position%s\n", YELLOW, arr[i], RESET);
        print_array_colored(arr, n, i, -1);
        create_delay();
        
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
    
    clear_screen();
    printf("%sCounting Sort - Final Result:%s\n", GREEN, RESET);
    print_array_colored(arr, n, -1, -1);
}

void counting_sort_for_radix_visual(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
    for (int i = 0; i < n; i++) {
        clear_screen();
        printf("%sRadix Sort - Counting digit %d%s\n", YELLOW, (arr[i] / exp) % 10, RESET);
        print_array_colored(arr, n, i, -1);
        create_delay();
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

void radix_sort_visual(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        clear_screen();
        printf("%sRadix Sort - Sorting by digit position %d%s\n", YELLOW, exp, RESET);
        print_array_colored(arr, n, -1, -1);
        create_delay();
        
        counting_sort_for_radix_visual(arr, n, exp);
    }
    
    clear_screen();
    printf("%sRadix Sort - Final Result:%s\n", GREEN, RESET);
    print_array_colored(arr, n, -1, -1);
}

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    int n;
    printf("%sWelcome to the Sorting Algorithm Visualizer!%s\n\n", BOLD, RESET);
    
    printf("Enter the number of elements (max 100): ");
    scanf("%d", &n);
    
    if (n <= 0 || n > 100) {
        printf("%sError: Invalid number of elements%s\n", RED, RESET);
        return 1;
    }
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf("%sError: Memory allocation failed%s\n", RED, RESET);
        return 1;
    }
    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % MAX_VALUE;
    }
    
    printf("\n%sGenerated array:%s\n", CYAN, RESET);
    print_array_colored(arr, n, -1, -1);
    
    while (1) {
        printf("\n%sChoose a sorting algorithm:%s\n", MAGENTA, RESET);
        printf("1. Bubble Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Heap Sort\n");
        printf("4. Counting Sort\n");
        printf("5. Radix Sort\n");
        printf("6. Gnome Sort\n");
        printf("7. Exit\n");
        
        int choice;
        printf("\nEnter your choice (1-7): ");
        scanf("%d", &choice);
        
        int* arr_copy = (int*)malloc(n * sizeof(int));
        if (!arr_copy) {
            printf("%sError: Memory allocation failed%s\n", RED, RESET);
            free(arr);
            return 1;
        }
        
        memcpy(arr_copy, arr, n * sizeof(int));
        
        switch (choice) {
            case 1:
                bubble_sort_visual(arr_copy, n);
                break;
            case 2:
                quick_sort_visual(arr_copy, n);
                break;
            case 3:
                heap_sort_visual(arr_copy, n);
                break;
            case 4:
                counting_sort_visual(arr_copy, n);
                break;
            case 5:
                radix_sort_visual(arr_copy, n);
                break;
            case 6:
                gnome_sort_visual(arr_copy, n);
                break;
            case 7:
                free(arr);
                free(arr_copy);
                printf("\n%sThank you for using the Sorting Algorithm Visualizer!%s\n", GREEN, RESET);
                return 0;
            default:
                printf("%sInvalid choice!%s\n", RED, RESET);
        }
        
        free(arr_copy);
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        clear_screen();
    }
    
    return 0;
}

// gcc -o sort_benchmark main.c bubble_sort.c counting_sort.c gnome_sort.c heap_sort.c quick_sort.c radix_sort.c utils.c -I../include