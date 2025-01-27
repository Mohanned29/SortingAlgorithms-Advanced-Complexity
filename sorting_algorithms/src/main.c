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
        printf("3. Exit\n");
        
        int choice;
        printf("\nEnter your choice (1-3): ");
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