#include "Tourism.h"
using namespace std;

void TravelPath() {
    cout << "\n===== 旅游景点导航 =====" << endl;
    for (int i = 0; i < G.vexNum; i++) {
        cout << G.vexs[i].id << "-" << G.vexs[i].name << "  ";
    }
    cout << endl;

    int startId;
    cout << "请输入起始点编号：";
    cin >> startId;

    if (startId < 0 || startId >= G.vexNum) {
        cout << "起始点编号不存在！" << endl;
        return;
    }

    PathList pList = nullptr;
    DFSTraverse(startId, pList);

    cout << "\n导游路线为：" << endl;
    PathNode* p = pList;
    int cnt = 0;

    while (p) {
        cnt++;
        cout << "路线" << cnt << "：";
        for (int i = 0; i < G.vexNum; i++) {
            int id = p->vexs[i];
            cout << G.vexs[id].name;
            if (i != G.vexNum - 1) cout << "→";
        }
        cout << endl;
        p = p->next;
    }

    if (cnt == 0) {
        cout << "未找到路线！" << endl;
    }

    FreePathList(pList);
}

// ================== 最短路径功能 ==================
void FindShortPathUI() {
    cout << "\n===== 最短路径查询 =====" << endl;
    for (int i = 0; i < G.vexNum; i++) {
        cout << i << "-" << G.vexs[i].name << "  ";
    }
    cout << endl;

    int s, e;
    cout << "请输入起点编号：";
    cin >> s;
    cout << "请输入终点编号：";
    cin >> e;

    // 合法性检查
    if (s < 0 || e < 0 || s >= G.vexNum || e >= G.vexNum) {
        cout << "编号非法！" << endl;
        return;
    }

    // 初始化路径数组为全0
    Edge path[50] = { 0 };
    int total = FindShortPath(s, e, path);

    // 统计有效路径长度
    int count = 0;
    while (path[count].weight != 0 && count < 50) {
        count++;
    }

    cout << "\n最短路径：";
    if (count == 0) {
        // 起点=终点的特殊情况
        cout << G.vexs[s].name;
    }
    else {
        cout << G.vexs[path[0].start].name;
        for (int i = 0; i < count; i++) {
            cout << " → " << G.vexs[path[i].end].name;
        }
    }
    cout << "\n总长度：" << total << "m" << endl;
}

// ================== 最小生成树（铺设电路） ==================
void DesignPath() {
    cout << "\n===== 景区电路铺设规划（最小生成树） =====" << endl;
    Edge path[50];
    int sum = FindMinTree(path);

    cout << "需要铺设的线路：" << endl;
    for (int i = 0; i < G.vexNum - 1; i++) {
        int u = path[i].start;
        int v = path[i].end;
        int w = path[i].weight;
        cout << G.vexs[u].name << " — " << G.vexs[v].name
            << "  长度：" << w << "m" << endl;
    }
    cout << "电路总长度：" << sum << "m" << endl;
}