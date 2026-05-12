#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#include "Huffman.h"
#include <fstream>
using namespace std;

const int WEIGHT_SIZE = 256;

typedef struct HEAD
{
    char type[4];
    int length;
    int weight[WEIGHT_SIZE];
} HEAD;

bool InitHead(const char* infile, HEAD& sHead, int weight[]);
unsigned char Str2byte(const char* pBinStr);
int Encode(const char* infile, unsigned char*& pBuffer, int& bufSize, HuffmanTree pHT, HuffmanCode pHC[]);
int Compress(const char* infile, const char* outfile, HuffmanTree pHT, HuffmanCode pHC[], HEAD& sHead);
void PrintWeight(int weight[]);

#endif