#include "quick_sort.h"

void quick_sort(int *array, int start, int end) {//快速排序
    //start=0,end=sizeof(array)/sizeof(array[0])-1或者start=1,end=sizeof(array)/sizeof(array[0])
    if (start >= end) {
        return;
    }
    int mid = array[(start + end) / 2];//以中间值为基准元素
    int left = start, right = end;
    while (left < right) {
        while (array[left] < mid) {//从左向基准比对,若左值比基准要小,则符合升序排列的标准,进行下一个元素的比对
            ++left;
        }
        while (array[right] > mid) {//从右向基准比对,若右值比基准要大,则符合升序排列的标准,进行下一个元素的比对
            --right;
        }
        if (left <= right) {//发现左右都有元素出现问题,则进行交换,此处必须要有等于号
            swap(array[left++], array[right--]);//swap之后进行将left+1,right-1
        }
    }
    quick_sort(array, start, right);
    quick_sort(array, left, end);
    return;
}