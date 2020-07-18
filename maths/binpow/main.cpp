#include<iostream>

using namespace std;

long long fun1(long long a, long long b) {/*递归法*/
    if (b == 0) {
        return 1;
    }
    long long base = fun1(a, b / 2);
    if (b % 2) {
        return base * base * a;
    }
    else {
        return base * base;
    }
}

long long fun2(long long a, long long b) {/*非递归法*/
    long long ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans *= a;
        }
        a *= a;
        b >>= 1;
    }
    return ans;
}

int main() {
    long long a, b;
    cin >> a >> b;
    cout << fun1(a, b) << " " << fun2(a, b);
    return 0;
}