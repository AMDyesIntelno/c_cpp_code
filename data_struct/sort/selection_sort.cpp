#include"selection_sort.h"

void selection_sort(int *array, int len) {//选择排序
    for (int i = 0; i < len; ++i) {
        int posi = i;//记录每一次检索的最小值的位置
        for (int j = i + 1; j < len; ++j) {
            if (array[j] < array[posi]) {//更新最小值的位置
                posi = j;
            }
        }
        swap(array[posi], array[i]);
    }
    return;
}