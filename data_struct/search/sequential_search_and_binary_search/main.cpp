/*顺序查找&二分查找*/
#include<iostream>
#include<cstdlib>

using namespace std;
typedef struct StaticSearchTable {
    int *data;//空出零号位
    int length;//记录长度
} *SST;

void Create_SST(SST &table, int size) {
    table->data = new int[size + 1];
    for (int i = 1; i <= size; ++i) {
        cin >> table->data[i];
    }
    table->length = size;
}

void Destory(SST &table) {
    delete[]table->data;
    delete table;
    table = nullptr;
}

void Print(SST table) {
    for (int i = 1; i <= table->length; ++i) {
        cout << table->data[i] << ' ';
    }
    cout << endl;
}

int Sequential_Search(SST table, int num) {
    for (int i = 1; i <= table->length; ++i) {
        if (table->data[i] == num) {
            return i;
        }
    }
    return 0;
}

int Binary_Search(SST table, int num) {
    int start = 1;
    int end = table->length;
    int mid = (start + end) / 2;
    if (table->data[end] >= table->data[start]) {
        while (start <= end) {
            if (table->data[mid] > num) {
                end = mid - 1;
            }
            else if (table->data[mid] < num) {
                start = mid + 1;
            }
            else {
                return mid;
            }
            mid = (start + end) / 2;
        }
    }
    else {
        while (start <= end) {
            if (table->data[mid] < num) {
                end = mid - 1;
            }
            else if (table->data[mid] > num) {
                start = mid + 1;
            }
            else {
                return mid;
            }
            mid = (start + end) / 2;
        }
    }
    return 0;
}

int main() {
    srand(time(nullptr));
    SST table = new StaticSearchTable;
    int size;
    cout << "------顺序查找------" << endl;
    cout << "数据量: ";
    cin >> size;
    cout << "输入数据(如1 2 3以空格隔开)" << endl;
    Create_SST(table, size);
    cout << "数据记录如下" << endl;
    Print(table);
    int num = rand() % (2 * table->length);
    cout << "检索" << num << "在顺序表中的位置" << endl;
    int posi = Sequential_Search(table, num);
    if (posi) {
        cout << "位于第" << posi << "个位置" << endl;
    }
    else {
        cout << "顺序表中无此元素" << endl;
    }
    cout << endl;
    Destory(table);
    table = new StaticSearchTable;
    cout << "------二分查找------" << endl;
    cout << "数据量: ";
    cin >> size;
    cout << "输入有序数据(如1 2 3以空格隔开)" << endl;
    Create_SST(table, size);
    cout << "数据记录如下" << endl;
    Print(table);
    num = rand() % (2 * table->length);
    cout << "检索" << num << "在顺序表中的位置" << endl;
    posi = Binary_Search(table, num);
    if (posi) {
        cout << "位于第" << posi << "个位置" << endl;
    }
    else {
        cout << "顺序表中无此元素" << endl;
    }
    cout << endl;
    Destory(table);
    return 0;
}