#include<iostream>
#include<string>

using namespace std;

void z_fun(string s, int *z) {
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i > r) {
            l = r = i;
            while (r < s.size() && s[r - l] == s[r]) {
                ++r;
            }
            z[i] = r - l;
            --r;
        }
        else {
            int k = i - l;
            if (z[k] < r - i + 1) {
                z[i] = z[k];
            }
            else {
                l = i;
                while (r < s.size() && s[r - l] == s[r]) {
                    ++r;
                }
                z[i] = r - l;
                --r;
            }
        }
    }
}

int main() {
    string a, b;
    cin >> a >> b;
    string c = b + "$" + a;
    int z[c.size()];
    z_fun(c, z);
    for (unsigned long i = b.size() + 1; i < c.size(); ++i) {
        if (z[i] == b.size()) {
            cout << i - b.size() - 1 << ' ';
        }
    }
    return 0;
}