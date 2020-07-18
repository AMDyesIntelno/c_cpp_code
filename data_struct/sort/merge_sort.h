#ifndef TEST_MERGE_SORT_H
#define TEST_MERGE_SORT_H

#include<iostream>

using namespace std;

void merge(int *array, int start, int mid, int end, int *temp);

void merge_sort(int *array, int start, int end, int *temp);

#endif //TEST_MERGE_SORT_H
