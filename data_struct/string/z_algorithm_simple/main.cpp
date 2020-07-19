#include<iostream>
#include<string>

using namespace std;

void simple(string c, int *z) {
    int j = 0;
    for (int i = 1; i < c.size(); ++i) {
        while (c[i + j] == c[j]) {
            ++z[i];
            ++j;
        }
        j = 0;
    }
}

int main() {
    string a, b, c;
    cin >> a >> b;
    c = b + "$" + a;
    int z[c.size()] = {0};
    simple(c, z);
    for (unsigned long i = b.size() + 1; i < c.size(); ++i) {
        if (z[i] == b.size()) {
            cout << i - b.size() - 1 << ' ';
        }
    }
    return 0;
}