/*稀疏矩阵与三元组*/
#include<iostream>

using namespace std;
#define MAX_SIZE 1000
typedef struct Triple {
    int x, y;
    int data;
} tri;
struct table {
    int n = 0, m = 0, sum = 0;//sum为a中的元素个数
    tri *a = nullptr;
};

void create(table *t) {
    int n, m, temp;
    int k = 1;
    cin >> n >> m;
    t->n = n, t->m = m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> temp;
            if (temp) {
                t->a[k].x = i;
                t->a[k].y = j;
                t->a[k].data = temp;
                ++k;
                ++t->sum;
            }
        }
    }
}

void print(table *t) {
    int k = 1;
    for (int i = 1; i <= t->n; ++i) {
        for (int j = 1; j <= t->m; ++j) {
            if (t->a[k].x == i && t->a[k].y == j) {
                cout << t->a[k].data << ' ';
                ++k;
            }
            else {
                cout << 0 << ' ';
            }
        }
        cout << endl;
    }
}

int get_max(table *t) {
    int m = t->a[1].data;
    for (int i = 1; i <= t->sum; ++i) {
        m = max(t->a[i].data, m);
    }
    return m;
}

void simple_transpose(table *t) {
    tri temp[MAX_SIZE];
    int k = 1;
    for (int i = 1; i <= t->m; ++i) {
        for (int j = 1; j <= t->sum; ++j) {
            if (t->a[j].y == i) {
                temp[k].x = t->a[j].y;
                temp[k].y = t->a[j].x;
                temp[k].data = t->a[j].data;
                ++k;
            }
        }
    }
    swap(t->n, t->m);
    t->a = temp;
}

void quick_transpose(table *t) {
    int *temp = new int[t->m + 1];
    fill(temp, temp + 1 + t->m, 0);
    for (int i = 1; i <= t->sum; ++i) {
        temp[t->a[i].y]++;
    }
    for (int i = 0; i < t->m; ++i) {
        temp[i + 1] += temp[i];
    }
    tri store[MAX_SIZE];
    for (int i = 1; i <= t->sum; ++i) {
        store[temp[t->a[i].y - 1] + 1].x = t->a[i].y;
        store[temp[t->a[i].y - 1] + 1].y = t->a[i].x;
        store[temp[t->a[i].y - 1] + 1].data = t->a[i].data;
        temp[t->a[i].y - 1]++;
    }
    swap(t->n, t->m);
    t->a = store;
}

int main() {
    table t;
    t.a = new tri[MAX_SIZE];
    create(&t);
    cout << "max: " << get_max(&t) << endl;
    //simple_transpose(&t);
    quick_transpose(&t);
    print(&t);
    return 0;
}