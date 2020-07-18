#include "quick_sort.h"
#include "bubble_sort.h"
#include "bucket_sort.h"
#include "count_sort.h"
#include "heap_sort.h"
#include "direct_insert_sort.h"
#include "half_insert_sort.h"
#include "merge_sort.h"
#include "radix_sort.h"
#include "selection_sort.h"
#include "shell_sort.h"

void print(int *array, int len) {
    for (int i = 0; i < len; ++i) {
        cout << array[i] << ' ';
    }
    cout << endl;
    return;
}

void recovery(int *array, int *backup, int len) {
    for (int i = 0; i < len; ++i) {
        array[i] = backup[i];
    }
    return;
}

int main() {
    int array[] = {1321, 5649, 98, 41, 518, 9, 41};
    int backup[] = {1321, 5649, 98, 41, 518, 9, 41};
    int len = sizeof(array) / sizeof(array[0]);
    quick_sort(array, 0, len - 1);
    print(array, len);
    recovery(array, backup, len);
    /**/
    bubble_sort(array, len);
    print(array, len);
    recovery(array, backup, len);
    /**/
    int bucket_num = 3;
    vector<int> *bucket = new vector<int>[bucket_num];
    bucket_sort(array, len, bucket_num, bucket);
    print(array, len);
    recovery(array, backup, len);
    delete[] bucket;
    /**/
    count_sort(array, len);
    print(array, len);
    recovery(array, backup, len);
    /**/
    heap_sort(array, len);
    print(array, len);
    recovery(array, backup, len);
    /**/
    direct_insert_sort(array, len);
    print(array, len);
    recovery(array, backup, len);
    /**/
    half_insert_sort(array, len);
    print(array, len);
    recovery(array, backup, len);
    /**/
    int *temp = new int[len];
    fill(temp, temp + len, 0);
    merge_sort(array, 0, len - 1, temp);
    print(array, len);
    recovery(array, backup, len);
    delete[] temp;
    /**/
    temp = new int[len];
    int *num_bucket = new int[10];
    fill(temp, temp + len, 0);
    fill(num_bucket, num_bucket + 10, 0);
    radix_sort(array, len, num_bucket, temp);
    print(array, len);
    recovery(array, backup, len);
    delete[] temp;
    delete[] num_bucket;
    /**/
    selection_sort(array, len);
    print(array, len);
    recovery(array, backup, len);
    /**/
    shell_sort(array, len);
    return 0;
}