#include "bubble_sort.h"

void bubble_sort(int *array, int len) {//冒泡排序
    for (int i = 1; i < len; i++) {//进行一次遍历将相邻的两个数修改为有序
        if (array[i] < array[i - 1]) {
            swap(array[i], array[i - 1]);
        }
    }
    for (int i = 1; i < len; i++) {//进行一次遍历检查是否完全有序
        if (array[i] < array[i - 1]) {
            bubble_sort(array, len);
        } else {
            continue;
        }
    }
    return;
}