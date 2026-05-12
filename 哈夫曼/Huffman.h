#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <iostream>
using namespace std;

const int N = 256;
const int M = 2 * N - 1;

struct HTNode
{
    int weigpHT;
    int parent;
    int lchild;
    int rchild;
};

typedef HTNode* HuffmanTree;

struct codetype
{
    int start;
    char bits[N];
};

struct HuffmanCode
{
    unsigned char symbol;
    codetype code;
};

void Select(HuffmanTree pHT, int nSize, int& x1, int& x2);
void CreateHuffmanTree(HuffmanTree pHT, int weight[]);
void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[]);
void PrintHuffmanTree(HuffmanTree pHT);
void PrintHuffmanCode(HuffmanCode pHC[]);

#endif