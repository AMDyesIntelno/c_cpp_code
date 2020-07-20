#include<iostream>
#include<cmath>

using namespace std;

inline double calculate(double x, char op, double y) {
    if (op == '+') {
        return x + y;
    }
    else if (op == '-') {
        return x - y;
    }
    else if (op == '*') {
        return x * y;
    }
    else {
        return (y == 0) ? -100000000 : x / y;//被除数不能为0
    }
}

void print(double a, double b, double c, double d, double e, double f, char op1, char op2, char op3) {
    cout << a << op1 << b << '=' << calculate(a, op1, b) << endl;
    cout << c << op2 << d << '=' << calculate(c, op2, d) << endl;
    cout << e << op3 << f << '=' << calculate(e, op3, f) << endl << endl;
}

void perm_char(double *int_array, char *char_array) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (calculate(calculate(calculate(int_array[0], char_array[i], int_array[1]), char_array[j], int_array[2]), char_array[k], int_array[3]) ==
                    24) {//((a?b)?c)?d,ch[0],ch[1],ch[2]
                    print(int_array[0], int_array[1], calculate(int_array[0], char_array[i], int_array[1]), int_array[2],
                          calculate(calculate(int_array[0], char_array[i], int_array[1]), char_array[j], int_array[2]), int_array[3], char_array[i], char_array[j], char_array[k]);
                }
            }
        }
    }
}

void perm_int(double *int_array, int int_start, int int_end, char *char_array) {
    if (int_start >= int_end) {//新的排列
        perm_char(int_array, char_array);
        return;
    }
    else {
        for (int i = int_start; i < int_end; ++i) {
            swap(int_array[i], int_array[int_start]);
            perm_int(int_array, int_start + 1, int_end, char_array);
            swap(int_array[i], int_array[int_start]);
        }
    }
}

int main() {
    char operate[4] = {'+', '-', '*', '/'};
    double array[4];
    cin >> array[0] >> array[1] >> array[2] >> array[3];
    perm_int(array, 0, 4, operate);
    return 0;
}