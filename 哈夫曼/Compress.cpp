#include "Compress.h"
#include "Huffman.h"
#include <cstring>
#include <iomanip>
using namespace std;

bool InitHead(const char* infile, HEAD& sHead, int weight[]) {
    ifstream inFile(infile, ios::binary);
    if (!inFile) {
        cerr << "文件打开失败: " << infile << endl;
        return false;
    }

    strcpy_s(sHead.type, sizeof(sHead.type), "HUF");
    sHead.length = 0;
    memset(weight, 0, WEIGHT_SIZE * sizeof(int));

    unsigned char ch;
    while (inFile.read((char*)&ch, 1)) {
        weight[ch]++;
        sHead.length++;
    }
    memcpy(sHead.weight, weight, WEIGHT_SIZE * sizeof(int));

    inFile.close();
    return true;
}

void PrintWeight(int weight[]) {
    cout << "\n原文件每个字符的权值为:\n";
    cout << "Byte\tWeight\n";
    for (int i = 0; i < WEIGHT_SIZE; i++) {
        if (weight[i] > 0)
            cout << "0x" << hex << setw(2) << setfill('0') << i << "\t" << dec << weight[i] << "\n";
    }
}

unsigned char Str2byte(const char* pBinStr) {
    unsigned char byte = 0;
    for (int i = 0; i < 8; i++) {
        if (pBinStr[i] == '1')
            byte |= (1 << (7 - i));
    }
    return byte;
}

int Encode(const char* infile, unsigned char*& pBuffer, int& bufSize, HuffmanTree pHT, HuffmanCode pHC[]) {
    ifstream inFile(infile, ios::binary);
    if (!inFile) return -1;

    pBuffer = new unsigned char[bufSize];
    int idx = 0;
    unsigned char curByte = 0;
    int bitCnt = 0;
    unsigned char ch;

    cout << "\n压缩后的文件编码:\n";
    while (inFile.read((char*)&ch, 1)) {
        int i = ch;
        for (int j = pHC[i].code.start; j < N; j++) {
            cout << pHC[i].code.bits[j];
            curByte <<= 1;
            if (pHC[i].code.bits[j] == '1') curByte |= 1;
            if (++bitCnt == 8) {
                pBuffer[idx++] = curByte;
                curByte = 0;
                bitCnt = 0;
            }
        }
    }
    if (bitCnt > 0) {
        curByte <<= (8 - bitCnt);
        pBuffer[idx++] = curByte;
    }

    inFile.close();
    bufSize = idx;
    return idx;
}

int Compress(const char* infile, const char* outfile, HuffmanTree pHT, HuffmanCode pHC[], HEAD& sHead) {
    int weight[WEIGHT_SIZE];
    if (!InitHead(infile, sHead, weight)) return -1;
    PrintWeight(weight);

    CreateHuffmanTree(pHT, weight);
    PrintHuffmanTree(pHT);

    HuffmanCoding(pHT, pHC);
    PrintHuffmanCode(pHC);

    int bufSize = sHead.length * 2;
    unsigned char* pBuffer = nullptr;
    int compSize = Encode(infile, pBuffer, bufSize, pHT, pHC);
    if (compSize == -1) { delete[] pBuffer; return -1; }

    ofstream outFile(outfile, ios::binary);
    if (!outFile) { delete[] pBuffer; return -1; }
    outFile.write((char*)&sHead, sizeof(sHead));
    outFile.write((char*)pBuffer, compSize);
    outFile.close();

    delete[] pBuffer;
    return compSize;
}