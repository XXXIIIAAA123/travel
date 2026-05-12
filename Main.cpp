#include "Graph.h"
#include "Tourism.h"
using namespace std;

int main() {
    int choice, id;
    while (true) {
        cout << "1. 创建景区景点图" << endl;
        cout << "2. 查询景点" << endl;
        cout << "3. 旅游景点导航" << endl;
        cout << "4. 最短路径查询" << endl;    
        cout << "5. 电路铺设规划" << endl;   
        cout << "0. 退出系统" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            CreateGraph();
            break;

        case 2:
            if (G.vexNum == 0) {
                cout << "请先创建景区图！" << endl;
                break;
            }
            cout << "请输入景点编号：";
            cin >> id;
            QueryVertex(G, id);
            break;

        case 3:
            if (G.vexNum == 0) {
                cout << "请先创建景区图！" << endl;
                break;
            }
            TravelPath();
            break;

        case 4:
            if (G.vexNum == 0) { cout << "请先创建图！" << endl; break; }
            FindShortPathUI();
            break;

        case 5:
            if (G.vexNum == 0) { cout << "请先创建图！" << endl; break; }
            DesignPath();
            break;

        case 0:
            cout << "退出成功！" << endl;
            return 0;

        default:
            cout << "输入错误！" << endl;
        }
    }
    return 0;
}