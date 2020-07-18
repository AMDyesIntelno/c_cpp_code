#include "base64.h"

int main() {
    string a = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    cout << a << endl;
    cout << encode(a);
    return 0;
}