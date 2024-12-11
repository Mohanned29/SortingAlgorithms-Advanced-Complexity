#include "../include/gnome_sort.h"

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
