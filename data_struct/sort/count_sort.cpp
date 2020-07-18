#include"count_sort.h"

void count_sort(int *array, int len) {//计数排序(桶排序低配版,也可以作为桶排序的辅助排序函数),小范围数据神器,大范围数据没卵用(不能出现负数)
    int _max = array[0];
    for (int i = 0; i < len; ++i) {
        _max = max(array[i], _max);
    }
    int *temp = new int[_max + 1];
    fill(temp, temp + 1 + _max, 0);
    for (int i = 0; i < len; ++i) {
        temp[array[i]]++;
    }
    int j = 0;
    for (int i = 0; i <= _max; ++i) {
        while (temp[i]) {
            array[j++] = i;
            --temp[i];
        }
    }
    delete[]temp;
    return;
}