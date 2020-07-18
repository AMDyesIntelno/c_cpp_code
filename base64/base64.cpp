#include "base64.h"

const char *base64_ch = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string encode(const string &str) {
    string temp;
    int len = str.size();
    int posi = 0, i = 0;
    char source[3] = {0};
    while (len--) {
        source[i++] = str[posi++];
        if (i == 3) {
            temp += base64_ch[(source[0] & 0xfc) >> 2];
            temp += base64_ch[((source[0] & 0x03) << 4)/*这里必须是4不能是2*/+ ((source[1] & 0xf0) >> 4)];
            temp += base64_ch[((source[1] & 0x0f) << 2) + ((source[2] & 0xc0) >> 6)];
            temp += base64_ch[source[2] & 0x3f];
            i = 0;
            source[0] = 0;
            source[1] = 0;
            source[2] = 0;
        }
    }
    if (i > 0) {
        temp += ((source[0] & 0xfc) >> 2) == 0 ? '=' : base64_ch[(source[0] & 0xfc) >> 2];
        temp += ((source[0] & 0x03) << 4)/*这里必须是4不能是2*/+ ((source[1] & 0xf0) >> 4) == 0 ? '=' : base64_ch[
                ((source[0] & 0x03) << 4)/*这里必须是4不能是2*/+ ((source[1] & 0xf0) >> 4)];
        temp += ((source[1] & 0x0f) << 2) + ((source[2] & 0xc0) >> 6) == 0 ? '=' : base64_ch[((source[1] & 0x0f) << 2) +
                                                                                             ((source[2] & 0xc0) >> 6)];
        temp += (source[2] & 0x3f) == 0 ? '=' : base64_ch[source[2] & 0x3f];
    }
    return temp;
}