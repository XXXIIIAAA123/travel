#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
using namespace std;

#define MAX_VERTEX_NUM 7
#define INF 1000000

typedef struct {
    int id;
    char name[20];
    char desc[100];
} Vertex;

typedef struct {
    Vertex vexs[MAX_VERTEX_NUM];
    int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexNum, edgeNum;
} MGraph;

typedef struct Path {
    int vexs[MAX_VERTEX_NUM];
    struct Path* next;
} PathNode, * PathList;

typedef struct {
    int start;
    int end;
    int weight;
} Edge;

extern MGraph G;


void CreateGraph();
void QueryVertex(const MGraph& G, int id);
void DFS(int nVex, bool bVisited[], int aPath[], int& nIndex, PathList& pList);
void DFSTraverse(int nVex, PathList& pList);
void FreePathList(PathList& pList);


int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
int FindMinTree(Edge aPath[]);

#endif