#pragma once
#include "Huffman.h"
#include "Compress.h"

void Init_Head(const char* infile, HEAD& sHead, HuffmanTree pHT);
void Uncompress(const char* infile, const char* outfile, HEAD& sHead, HuffmanTree pHT, HuffmanCode pHC[]);