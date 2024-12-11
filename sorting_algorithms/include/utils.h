#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void generate_random_array(int arr[], int n, int max_value);
void print_array(int arr[], int n);
double measure_time(void (*sort_function)(int[], int), int arr[], int n);

#endif
