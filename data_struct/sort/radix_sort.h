#ifndef TEST_RADIX_SORT_H
#define TEST_RADIX_SORT_H

#include<iostream>

using namespace std;

int radix_get_max(int *array, int len);

void radix_sort_core(int *array, int len, int exp, int *bucket, int *temp);

void radix_sort(int *array, int len, int *bucket, int *temp);

#endif //TEST_RADIX_SORT_H
