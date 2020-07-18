#ifndef FILE_COMPRESSION_SYSTEM_ENCRYPT_DECRYPT_H
#define FILE_COMPRESSION_SYSTEM_ENCRYPT_DECRYPT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void encrypt(string &key, string &plaintext, string &ciphertext);

void decrypt(string &key, string &plaintext, string &ciphertext);

#endif //FILE_COMPRESSION_SYSTEM_ENCRYPT_DECRYPT_H
