/*Eratosthenes 筛法 (埃拉托斯特尼筛法)*/
#include<iostream>

using namespace std;
int a[1000001];

void Eratosthenes(long long n) {
    fill(a, a + 1000001, 1);/*将数组填充为1，假设当前范围内的数均为素数，然后开始筛选*/
    for (long long i = 2; i <= n; ++i) {
        /*先用2去筛，即把2留下，把2的倍数剔除掉；再用下一个素数，也就是3筛，把3留下，把3的倍数剔除掉；接下去用下一个素数5筛，把5留下，把5的倍数剔除掉；不断重复下去......*/
        for (long long j = i * i; j <= n; j += i) {/*此处应从i的平方开始计算，以减少计算量*/
            a[j] = 0;
        }
    }
}

int main() {
    long long n;
    cin >> n;
    Eratosthenes(n);
    for (long long i = 2; i <= n; ++i) {
        if (a[i]) {
            cout << i << ' ';
        }
    }
    return 0;
}