#include<iostream>
#include<string>

using namespace std;

void getfail(string s, int *f) {
    f[0] = 0, f[1] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int j = f[i];
        while (j && s[i] != s[j]) {
            j = f[j];
        }
        f[i + 1] = s[i] == s[j] ? j + 1 : 0;
    }
}

void kmp(string a, string b, int *f) {
    getfail(b, f);
    int i = 0, j = 0;
    while (i < a.size()) {
        if (a[i] == b[j]) {
            ++i;
            ++j;
        }
        else if (j) {
            j = f[j];
        }
        else {
            ++i;
        }
        if (j == b.size()) {
            cout << i - j << endl;
        }
    }
}

int main() {
    string a, b;
    cin >> a >> b;
    int f[b.size() + 1];
    kmp(a, b, f);
    return 0;
}