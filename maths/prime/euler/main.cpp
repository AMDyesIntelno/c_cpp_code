/*Euler 筛法 (欧拉筛法)*/
#include<iostream>

using namespace std;
long long a[1000001];//a用于记录已经判断出是素数的数
bool b[1000001];//b用于判断当前数字是否为素数
void Euler(long long n) {
    fill(b, b + 1000001, 1);/*将数组填充为1，假设当前范围内的数均为素数，然后开始筛选*/
    b[0] = false;
    b[1] = false;/*0，1均不是素数*/
    int cnt = 0;/*确定素数在数组a中的放置位置*/
    for (long long i = 2; i <= n; ++i) {
        if (b[i]) {
            a[cnt++] = i;/*将当前素数储存并记录*/
        }
        for (int j = 0; j < cnt && i * a[j] <= n; ++j) {
            b[i * a[j]] = false;/*已储存素数的倍数均为合数*/
            if (!(i % a[j])) {/*i%a[j]==0表明i是一个素数的倍数，说明i在之前已经被筛过了，无需再筛*/
                break;
            }
        }
    }
}

int main() {
    long long n;
    cin >> n;
    Euler(n);
    for (long long i = 0; i <= n; ++i) {
        if (a[i]) {
            cout << a[i] << ' ';
        }
    }
    return 0;
}