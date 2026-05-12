#include "Graph.h"
#include <fstream>
using namespace std;

MGraph G;

void CreateGraph() {
    ifstream finVex("Vex.txt");
    ifstream finEdge("Edge.txt");

    if (!finVex || !finEdge) {
        cout << "文件打开失败！" << endl;
        return;
    }

    finVex >> G.vexNum;

    for (int i = 0; i < G.vexNum; i++) {
        for (int j = 0; j < G.vexNum; j++) {
            G.edges[i][j] = INF;
        }
    }

    for (int i = 0; i < G.vexNum; i++) {
        finVex >> G.vexs[i].id;
        finVex >> G.vexs[i].name;
        finVex.ignore();
        finVex.getline(G.vexs[i].desc, 100);
    }

    int v1, v2, w;
    G.edgeNum = 0;
    while (finEdge >> v1 >> v2 >> w) {
        G.edges[v1][v2] = w;
        G.edges[v2][v1] = w;
        G.edgeNum++;
    }

    finVex.close();
    finEdge.close();
    cout << "图创建成功！" << endl;
}

void QueryVertex(const MGraph& G, int id) {
    if (id < 0 || id >= G.vexNum) {
        cout << "景点编号不存在！" << endl;
        return;
    }

    cout << "\n===== 景点详情 =====" << endl;
    cout << "编号：" << G.vexs[id].id << endl;
    cout << "名称：" << G.vexs[id].name << endl;
    cout << "描述：" << G.vexs[id].desc << endl;
    cout << "相邻景点：";
    for (int i = 0; i < G.vexNum; i++) {
        if (G.edges[id][i] != INT_MAX && id != i) {
            cout << G.vexs[i].name << "(" << G.edges[id][i] << "m) ";
        }
    }
    cout << endl;
}

void DFS(int nVex, bool bVisited[], int aPath[], int& nIndex, PathList& pList) {
    bVisited[nVex] = true;
    aPath[nIndex++] = nVex;

    if (nIndex == G.vexNum) {
        PathNode* pNew = new PathNode;
        for (int i = 0; i < G.vexNum; i++) {
            pNew->vexs[i] = aPath[i];
        }
        pNew->next = nullptr;

        if (!pList) pList = pNew;
        else {
            PathNode* p = pList;
            while (p->next) p = p->next;
            p->next = pNew;
        }
    }
    else {
        for (int i = 0; i < G.vexNum; i++) {
            if (G.edges[nVex][i] != INT_MAX && !bVisited[i]) {
                DFS(i, bVisited, aPath, nIndex, pList);
            }
        }
    }

    nIndex--;
    bVisited[nVex] = false;
}

void DFSTraverse(int nVex, PathList& pList) {
    pList = nullptr;
    bool bVisited[MAX_VERTEX_NUM] = { false };
    int aPath[MAX_VERTEX_NUM];
    int nIndex = 0;
    DFS(nVex, bVisited, aPath, nIndex, pList);
}

void FreePathList(PathList& pList) {
    PathNode* p = pList;
    while (p) {
        PathNode* q = p->next;
        delete p;
        p = q;
    }
    pList = nullptr;
}

// ================== Dijkstra 最短路径 ==================
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
    int dist[MAX_VERTEX_NUM];
    int path[MAX_VERTEX_NUM];
    bool visited[MAX_VERTEX_NUM] = { false };

    // 初始化
    for (int i = 0; i < G.vexNum; i++) {
        dist[i] = G.edges[nVexStart][i];
        path[i] = nVexStart;
    }
    dist[nVexStart] = 0;
    visited[nVexStart] = true;

    // Dijkstra 核心
    for (int i = 1; i < G.vexNum; i++) {
        int min = INF;
        int u = -1;
        for (int j = 0; j < G.vexNum; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < G.vexNum; v++) {
            if (!visited[v] && G.edges[u][v] != INF && dist[v] > dist[u] + G.edges[u][v]) {
                dist[v] = dist[u] + G.edges[u][v];
                path[v] = u;
            }
        }
    }

    // 还原路径到 aPath
    int count = 0;
    int cur = nVexEnd;
    while (cur != nVexStart) {
        int pre = path[cur];
        aPath[count].start = pre;
        aPath[count].end = cur;
        aPath[count].weight = G.edges[pre][cur];
        count++;
        cur = pre;
    }

    // 反转路径（从起点到终点）
    for (int i = 0; i < count / 2; i++) {
        Edge temp = aPath[i];
        aPath[i] = aPath[count - 1 - i];
        aPath[count - 1 - i] = temp;
    }

    //  关键：添加终止标记，防止打印时越界
    if (count < 50) {
        aPath[count].weight = 0;
    }

    return dist[nVexEnd];
}

// ================== Prim 最小生成树（铺设电路） ==================
int FindMinTree(Edge aPath[]) {
    bool visited[MAX_VERTEX_NUM] = { false };
    int minEdge[MAX_VERTEX_NUM];
    int adjVertex[MAX_VERTEX_NUM];
    int sum = 0;
    int count = 0;

    visited[0] = true;
    for (int i = 0; i < G.vexNum; i++) {
        minEdge[i] = G.edges[0][i];
        adjVertex[i] = 0;
    }

    for (int i = 1; i < G.vexNum; i++) {
        int min = INF;
        int k = -1;
        for (int j = 0; j < G.vexNum; j++) {
            if (!visited[j] && minEdge[j] < min) {
                min = minEdge[j];
                k = j;
            }
        }
        if (k == -1) break;

        visited[k] = true;
        aPath[count].start = adjVertex[k];
        aPath[count].end = k;
        aPath[count].weight = min;
        sum += min;
        count++;

        for (int j = 0; j < G.vexNum; j++) {
            if (!visited[j] && G.edges[k][j] < minEdge[j]) {
                minEdge[j] = G.edges[k][j];
                adjVertex[j] = k;
            }
        }
    }
    return sum;
}