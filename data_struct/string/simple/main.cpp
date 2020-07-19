#include<iostream>
#include<string>

using namespace std;

void simple(string a, string b) {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            if (j == b.size()) {
                cout << "posi: " << i << endl;
                break;
            }
            if (a[i + j] == b[j]) {
                continue;
            }
            else {
                break;
            }
        }
    }
}

int main() {
    string a, b;
    cin >> a >> b;
    simple(a, b);
    return 0;
}