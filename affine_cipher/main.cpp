/*仿射密码暴力破解*/
#include<iostream>
#include<string>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

int main() {
    string letter = "abcdefghijklmnopqrstuvwxyz";
    string word, flag;
    cin >> word;
    /*word:falszztysyjzyjkywjrztyjztyynaryjkyswarztyegyyj*/
    /*flag:firstthesentenceandthentheevidencesaidthequeen*/
    for (int a = 1; a < letter.size(); ++a) {
        if (gcd(a, letter.size()) == 1) {
            for (int b = 0; b < letter.size(); ++b) {
                for (char i : word) {
                    for (int j = 0; j < letter.size(); ++j) {
                        if (i == letter[(a * j + b) % letter.size()]) {
                            flag += letter[j];
                        }
                    }
                }
                cout << flag << endl;
                flag.erase();
            }
        }
    }
    return 0;
}