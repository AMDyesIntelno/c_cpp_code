/*筛法求多个数的欧拉函数*/
#include<iostream>

using namespace std;
int phi[1000001];

void phi_table(int n) {
    phi[1] = 1;
    /*φ(1)=1*/
    for (int i = 2; i <= n; ++i) {
        if (!phi[i]) {/*保证i是质因数*/
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) {
                    phi[j] = j;/*phi数组的元素与欧拉函数值一一对应*/
                }
                phi[j] = phi[j] / i * (i - 1);/*i作为当前for循环中j的因数*/
                /*例如求6的欧拉函数时，以i=2作为j的循环，以i=3作为j的循环
                  在每一个循环中，当j=6时会以i作为质因数求解欧拉函数*/
                /*ans/i*(i-1)=ans*(1-1/i)*/
                /*φ(x)=x(1-1/p(1))(1-1/p(2))(1-1/p(3))…..(1-1/p(n))*/
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    phi_table(n);
    for (int i = 1; i <= n; ++i) {
        cout << phi[i] << ' ';
    }
    return 0;
}