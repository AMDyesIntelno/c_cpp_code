#include "Encrypt_decrypt.h"
#include "Huffman.h"
#include "File_operation.h"

int main(int argc, char *argv[]) {
    string name, text, key, plaintext, ciphertext;
    vector<string> path;
    int sum, size = 0;
    int weight[16] = {0};
    H_Tree HT = NULL;
    H_Code HC = NULL;
    if (strcmp(argv[1], "-h") == 0) {//help
        cout << "tar: ./xxxx -t file1 file2 file3 [-p password] -o file_out" << endl;
        cout << "extract: ./xxxx -e file [-p password]" << endl;
        /*
         -t /home/zen/asdf /home/zen/ubuntu_setup_env.sh -o /home/zen/out
         -e /home/zen/out
        */
    }
    else if (strcmp(argv[1], "-t") == 0) {//压缩
        int i = 2;
        while (i < argc && strcmp(argv[i], "-p") != 0 && strcmp(argv[i], "-o") != 0) {//分离文件名,并将文件夹中的所有文件找到
            name = argv[i];
            list_dir(name, path);
            if (size == path.size()) {
                path.push_back(name);
            }
            size = path.size();
            ++i;
        }
        for (int j = 0; j < path.size(); ++j) {
            cout << path[j] << endl;
            tar_convert_file(path[j], text);//读取文件内容
        }
        if (i < argc && strcmp(argv[i], "-p") == 0) {//如果存在-p 则记录加密密钥
            key = argv[i + 1];
            i += 2;
        }
        if (i < argc && strcmp(argv[i], "-o") == 0) {//记录输出的文件名
            name = argv[i + 1];
        }
        get_weight(text, weight, plaintext);//统计各个字符的权重
        Create_Huffman_Tree(HT, weight);
        Create_Huffman_Code(HT, HC);
        encode(plaintext, text, HC);
        if (key.size() > 0) {
            encrypt(key, plaintext, ciphertext);
        }
        else {
            ciphertext.erase();
            ciphertext = plaintext;
        }
        binary_to_hex(ciphertext);
        write_file(name, ciphertext);
    }
    else if (strcmp(argv[1], "-e") == 0) {//解压
        name = argv[2];
        if (argc > 3) {
            if (strcmp(argv[3], "-p") == 0) {
                if (argc > 4) {
                    key = argv[4];
                }
            }
        }
        if (key.size() > 0) {
            extract_convert_file(name, ciphertext);
            decrypt(key, plaintext, ciphertext);
        }
        else {
            extract_convert_file(name, plaintext);
        }
        sum = recover(weight, plaintext);
        Create_Huffman_Tree(HT, weight);
        decode(plaintext, HT, sum);
        spilt_and_extract(plaintext);
    }
    delete HT;
    HT = NULL;
    delete HC;
    HC = NULL;
    return 0;
}