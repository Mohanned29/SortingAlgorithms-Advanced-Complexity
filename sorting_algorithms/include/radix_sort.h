#ifndef RADIX_SORT_H
#define RADIX_SORT_H

int key(int x, int i);
void sort_aux(int arr[], int n, int i);
void radix_sort(int arr[], int n, int k);

#endif
