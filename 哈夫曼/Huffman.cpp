#include "Huffman.h"
#include <iomanip>
using namespace std;

void Select(HuffmanTree pHT, int nSize, int& x1, int& x2) {
    int min1, min2;
    min1 = min2 = 0;
    while (min1 < nSize && pHT[min1].parent != -1) min1++;
    min2 = min1 + 1;
    while (min2 < nSize && pHT[min2].parent != -1) min2++;

    for (int i = 0; i < nSize; i++) {
        if (pHT[i].parent == -1) {
            if (pHT[i].weigpHT < pHT[min1].weigpHT) {
                min2 = min1;
                min1 = i;
            }
            else if (i != min1 && pHT[i].weigpHT < pHT[min2].weigpHT) {
                min2 = i;
            }
        }
    }
    x1 = min1;
    x2 = min2;
}

void CreateHuffmanTree(HuffmanTree pHT, int weight[]) {
    for (int i = 0; i < N; i++) {
        pHT[i].weigpHT = weight[i];
        pHT[i].parent = -1;
        pHT[i].lchild = -1;
        pHT[i].rchild = -1;
    }
    for (int i = N; i < M; i++) {
        pHT[i].weigpHT = 0;
        pHT[i].parent = -1;
        pHT[i].lchild = -1;
        pHT[i].rchild = -1;
    }

    for (int i = N; i < M; i++) {
        int x1, x2;
        Select(pHT, i, x1, x2);
        pHT[x1].parent = i;
        pHT[x2].parent = i;
        pHT[i].lchild = x1;
        pHT[i].rchild = x2;
        pHT[i].weigpHT = pHT[x1].weigpHT + pHT[x2].weigpHT;
    }
}

void HuffmanCoding(HuffmanTree pHT, HuffmanCode pHC[]) {
    for (int i = 0; i < N; i++) {
        pHC[i].symbol = (unsigned char)i;
        pHC[i].code.start = N - 1;
        for (int j = 0; j < N; j++) pHC[i].code.bits[j] = '0';
    }

    for (int i = 0; i < N; i++) {
        int cur = i;
        int p = pHT[cur].parent;
        while (p != -1) {
            if (pHT[p].lchild == cur)
                pHC[i].code.bits[pHC[i].code.start--] = '0';
            else
                pHC[i].code.bits[pHC[i].code.start--] = '1';
            cur = p;
            p = pHT[cur].parent;
        }
        pHC[i].code.start++;
    }
}

void PrintHuffmanTree(HuffmanTree pHT) {
    cout << "\n哈夫曼树的每个节点信息为:\n";
    cout << "Byte\tWeight\tParent\tLchild\tRchild\n";
    for (int i = 0; i < M; i++) {
        if (pHT[i].weigpHT > 0 || i < N) {
            cout << "pHT[" << i << "]\t"
                << pHT[i].weigpHT << "\t"
                << pHT[i].parent << "\t"
                << pHT[i].lchild << "\t"
                << pHT[i].rchild << "\n";
        }
    }
}

void PrintHuffmanCode(HuffmanCode pHC[]) {
    cout << "\n先序遍历哈夫曼树输出编码信息:\n";
    cout << "Byte\tHufCode\n";
    for (int i = 0; i < N; i++) {
        if (pHC[i].code.start < N) {
            cout << "0x" << hex << setw(2) << setfill('0') << (int)pHC[i].symbol << "\t";
            for (int j = pHC[i].code.start; j < N; j++)
                cout << pHC[i].code.bits[j];
            cout << dec << "\n";
        }
    }
}