#include<iostream>

using namespace std;

long long fun(long long a, long long b, long long c) {
    if (b == 0) {
        return 1;
    }
    long long base = fun(a, b / 2, c);
    if (b % 2) {
        return base * base * a % c;
    }
    else {
        return base * base % c;
    }
}

int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    cout << a << "^" << b << " mod " << c << "=" << fun(a, b, c) % c;
    return 0;
}