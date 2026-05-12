#include "Uncompress.h"
#include "Huffman.h"
#include "Compress.h"
#include <fstream>
#include <iomanip>
using namespace std;

void Init_Head(const char* infile, HEAD& sHead, HuffmanTree pHT) {
    ifstream inFile(infile, ios::binary);
    if (!inFile) { cerr << "解压文件打开失败\n"; return; }
    inFile.read((char*)&sHead, sizeof(sHead));
    CreateHuffmanTree(pHT, sHead.weight);
    inFile.close();
}

void Uncompress(const char* infile, const char* outfile, HEAD& sHead, HuffmanTree pHT, HuffmanCode pHC[]) {
    ifstream inFile(infile, ios::binary);
    ofstream outFile(outfile, ios::binary);
    if (!inFile || !outFile) { cerr << "文件打开失败\n"; return; }

    inFile.seekg(sizeof(sHead), ios::beg);
    HuffmanCoding(pHT, pHC);

    int root = M - 1;
    int cur = root;
    unsigned char ch;
    int count = 0;

    while (inFile.read((char*)&ch, 1) && count < sHead.length) {
        for (int i = 7; i >= 0; i--) {
            if (pHT[cur].lchild == -1 && pHT[cur].rchild == -1) {
                outFile.write((char*)&cur, 1);
                if (++count >= sHead.length) break;
                cur = root;
            }
            int bit = (ch >> i) & 1;
            cur = (bit == 0) ? pHT[cur].lchild : pHT[cur].rchild;
        }
    }
    if (pHT[cur].lchild == -1 && pHT[cur].rchild == -1 && count < sHead.length)
        outFile.write((char*)&cur, 1);

    inFile.close();
    outFile.close();
}