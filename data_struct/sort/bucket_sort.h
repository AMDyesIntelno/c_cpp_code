#ifndef TEST_BUCKET_SORT_H
#define TEST_BUCKET_SORT_H

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int get_max(int *array, int len);

int get_min(int *array, int len);

void count_sort(vector<int> &bucket);

void bucket_sort(int *array, int len, int bucket_num, vector<int> *&bucket);

#endif //TEST_BUCKET_SORT_H
