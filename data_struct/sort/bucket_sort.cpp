#include "bucket_sort.h"

int get_max(int *array, int len) {//获取上界
    int _max = array[0];
    for (int i = 1; i < len; ++i) {
        _max = max(_max, array[i]);
    }
    return _max;
}

int get_min(int *array, int len) {//获取下界
    int _min = array[0];
    for (int i = 1; i < len; ++i) {
        _min = min(_min, array[i]);
    }
    return _min;
}

void count_sort(vector<int> &bucket) {//计数排序(不能出现负数)
    if (bucket.size()) {
        int _max = bucket[0];
        for (int i = 0; i < bucket.size(); ++i) {
            _max = max(_max, bucket[i]);
        }
        int *temp = new int[_max + 1];
        fill(temp, temp + 1 + _max, 0);
        for (int i = 0; i < bucket.size(); ++i) {
            temp[bucket[i]]++;
        }
        int j = 0;
        for (int i = 0; i <= _max; ++i) {
            while (temp[i]) {
                bucket[j++] = i;
                --temp[i];
            }
        }
        delete[]temp;
    }
    return;
}

void bucket_sort(int *array, int len, int bucket_num, vector<int> *&bucket) {//桶排序(不能出现负数)
    int _min = get_min(array, len), _max = get_max(array, len);
    int bucket_size = (_max - _min) / bucket_num + 1;//桶中数字的取值范围
    for (int i = 0; i < bucket_num; ++i) {
        bucket[i].clear();//清空
    }
    for (int i = 0; i < len; ++i) {//将不同的数划分到不同的桶中(垃圾分类doge
        bucket[(array[i] - _min) / bucket_size].push_back(array[i]);
    }
    int k = 0;
    for (int i = 0; i < bucket_num; ++i) {
        count_sort(bucket[i]);
        for (int j = 0; j < bucket[i].size(); ++j) {
            array[k++] = bucket[i][j];
        }
    }
    return;
}