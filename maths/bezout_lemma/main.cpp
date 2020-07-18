/*贝祖等式*/
#include<iostream>

using namespace std;
int s[3] = {1, 0};
int t[3] = {0, 1};

int gcd(int a, int b) {
    if (a % b == 0) {
        return b;
    }
    else {
        s[2] = s[0] - (a / b) * s[1];
        t[2] = t[0] - (a / b) * t[1];
        s[0] = s[1], s[1] = s[2], t[0] = t[1], t[1] = t[2];
        return gcd(b, a % b);
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << "gcd: " << gcd(a, b) << " s:" << s[1] << " t:" << t[1];
    return 0;
}