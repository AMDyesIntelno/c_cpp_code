#include"half_insert_sort.h"

int binary_search(int *array, int start, int end, int data) {//二分查找
    int mid = (start + end) / 2;
    if (start >= end) {//这里有等于号
        return mid;
    }
    if (array[mid] > data) {
        return binary_search(array, start, mid, data);
    }
    else {
        return binary_search(array, mid + 1, end, data);
    }
}

void half_insert_sort(int *array, int len) {//折半插入排序
    for (int i = 1; i < len; ++i) {//从第二个元素开始遍历,不用管第一个,因为在插入阶段会遍历到第一个元素
        int posi = binary_search(array, 0, i, array[i]), temp = array[i], j;//通过二分查找确认插入位置
        for (j = i; j > posi; --j) {
            array[j] = array[j - 1];//将元素后移
        }
        array[j] = temp;//将元素填入空位
    }
    return;
}