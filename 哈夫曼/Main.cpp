#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include "Huffman.h"
#include "Compress.h"
#include "Uncompress.h"
#include <iomanip>
using namespace std;

int main() {
    SetConsoleOutputCP(936);
    SetConsoleCP(936);

    char infile[256];
    cout << "========== Huffman文件压缩==========\n";
    cout << "请输入文件名: ";
    cin.getline(infile, 256);

    char out_compress[256];
    strcpy_s(out_compress, infile);
    strcat_s(out_compress, ".huf");

    const char* filename = strrchr(infile, '\\');
    if (filename == nullptr) filename = infile; // 如果没有路径，直接用文件名
    else filename++; // 跳过'\'

    char out_uncompress[256];
    strcpy_s(out_uncompress, "un_");
    strcat_s(out_uncompress, filename); // 正确拼接，得到 un_a.bmp

    HTNode pHT[M];
    HuffmanCode pHC[N];
    HEAD sHead;

    int compSize = Compress(infile, out_compress, pHT, pHC, sHead);
    if (compSize == -1) {
        system("pause");
        return -1;
    }

    double rate = 100.0 * (sHead.length - compSize - sizeof(sHead)) / sHead.length;
    cout << "\n" << sHead.length << " 字节\n";
    cout << "生成压缩文件: " << out_compress << "\n";
    cout << compSize + (int)sizeof(sHead) << " 字节\n";
    cout << "压缩比率: " << fixed << setprecision(3) << rate << "%\n";

    cout << "\n开始解压...\n";
    Init_Head(out_compress, sHead, pHT);
    Uncompress(out_compress, out_uncompress, sHead, pHT, pHC);
    cout << "解压成功，文件: " << out_uncompress << "\n";

    system("pause");
    return 0;
}