/*求单个数的欧拉函数值*/
#include<iostream>
#include<cmath>

using namespace std;

int euler_phi(int n) {
    int m = int(sqrt(n + 0.5));
    int ans = n;
    for (int i = 2; i <= m; ++i) {
        /*φ(x)=x(1-1/p(1))(1-1/p(2))(1-1/p(3))…..(1-1/p(n))*/
        if (n % i == 0) {/*判断i是否为n的质因数*/
            ans = ans / i * (i - 1);/*先进行除法运算避免溢出*/
            /*ans/i*(i-1)=ans*(1-1/i)*/
            while (n % i == 0) {
                n /= i;/*保证n在遇到下一个质因数之前不会再进行计算*/
                /*假定n=20，n可由质因数累积而成，n=2*2*5
                  显然4为n的因数，但不是质因数，在该while循环中
                  4被除去，因此可以保证下一次运算必定为质因数*/
            }
        }
    }
    if (n > 1) {
        ans = ans / n * (n - 1);/*最后剩下的一个质因数*/
        /*例如n=5，与n互质的数为1,2,3,4
          在上一步的for循环中没有符合条件的质因数
          说明n是质数，所以φ(n)=n-1
          又例如n=6，在上一步的for循环中只有2被筛出
          n=3，此时n为最后一个质因数
          φ(x)=x(1-1/p(1))(1-1/p(2))(1-1/p(3))…..(1-1/p(n))
          φ(x)=ans(1-1/p(n))
          综合两种情况将其写成ans=ans/n*(n-1)
          */
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    cout << euler_phi(n);
    return 0;
}