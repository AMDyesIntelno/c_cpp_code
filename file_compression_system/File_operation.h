#ifndef FILE_COMPRESSION_SYSTEM_FILE_OPERATION_H
#define FILE_COMPRESSION_SYSTEM_FILE_OPERATION_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <ios>
#include <dirent.h>
#include <vector>

using namespace std;

bool list_dir(const string& posi, vector<string> &path);

void tar_convert_file(const string &name, string &text);

void extract_convert_file(const string &name, string &text);

void spilt_and_extract(string &plaintext);

void binary_to_hex(string &text);

void write_file(const string &name, string &text);

#endif //FILE_COMPRESSION_SYSTEM_FILE_OPERATION_H
