/*Floyd算法,邻接矩阵表示*/
#include<iostream>

#define INF INT32_MAX/2
#define _MAX 21
using namespace std;
typedef enum {
    DN, UDN
} Graphkind;//带权有向图,带权无向图
typedef struct Arc {
    int weight = 0;//带权图记录权重,无权图记录是否链接
} Martix[_MAX][_MAX];//从(1,1)开始存
typedef struct Martrix_Graph {
    char vertex[_MAX];//顶点的值
    Martix Mar;//邻接矩阵
    Graphkind kind;//图的类型
    int _vertex, _arc;//顶点数量,弧数量
} *M_G;
bool visited[_MAX] = {false};

inline int find(M_G graph, char item) {//查找当前值对应的序号,用于确定其在邻接矩阵的行或列
    for (int i = 1; i <= graph->_vertex; ++i) {
        if (graph->vertex[i] == item) {
            return i;
        }
    }
    return 0;
}

void Create_DN(M_G &graph) {//创建带权有向图
    cout << "顶点数量: ";
    cin >> graph->_vertex;
    cout << "弧数量: ";
    cin >> graph->_arc;
    cout << "输入顶点的值:" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        cin >> graph->vertex[i];
    }
    for (int i = 0; i < _MAX; ++i) {
        for (int j = 0; j < _MAX; ++j) {
            graph->Mar[i][j].weight = INF;
        }
    }
    cout << "输入弧尾,弧头和弧的权重:" << endl;
    char v1, v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    for (int i = 1; i <= graph->_arc; ++i) {
        cin >> v2 >> v1 >> weight;
        if (find(graph, v2) == 0 || find(graph, v1) == 0) {
            exit(-1);
        }
        graph->Mar[find(graph, v2)][find(graph, v1)].weight = weight;
    }

}

void Create_UDN(M_G &graph) {//创建带权无向图
    cout << "顶点数量: ";
    cin >> graph->_vertex;
    cout << "弧数量: ";
    cin >> graph->_arc;
    cout << "输入顶点的值:" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        cin >> graph->vertex[i];
    }
    for (int i = 0; i < _MAX; ++i) {
        for (int j = 0; j < _MAX; ++j) {
            graph->Mar[i][j].weight = INF;
        }
    }
    cout << "输入弧尾,弧头和弧的权重:" << endl;
    char v1, v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    for (int i = 1; i <= graph->_arc; ++i) {
        cin >> v2 >> v1 >> weight;
        if (find(graph, v2) == 0 || find(graph, v1) == 0) {
            exit(-1);
        }
        graph->Mar[find(graph, v2)][find(graph, v1)].weight = weight;
        graph->Mar[find(graph, v1)][find(graph, v2)].weight = weight;
    }
}

void Create_Graph(M_G &graph) {
    cout << "0:创建带权有向图 1:创建带权无向图" << endl;
    cout << "选项: ";
    graph = new Martrix_Graph;
    cin >> (int &) graph->kind;
    switch (graph->kind) {
        case DN:
            Create_DN(graph);
            break;
        case UDN:
            Create_UDN(graph);
            break;
        default:
            cout << "ERROR!" << endl;
            break;
    }
}

void Floyd(M_G graph, int weight[][_MAX], int path[][_MAX]) {
    for (int i = 1; i <= graph->_vertex; ++i) {
        for (int j = 1; j <= graph->_vertex; ++j) {
            if (i == j) {
                weight[i][j] = 0;
                continue;
            }
            weight[i][j] = graph->Mar[i][j].weight;
        }
    }
    for (int i = 1; i <= graph->_vertex; ++i) {
        for (int j = 1; j <= graph->_vertex; ++j) {
            path[i][j] = j;
        }
    }
    cout << "初始化..." << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        for (int j = 1; j <= graph->_vertex; ++j) {
            if (weight[i][j] == INF) {
                cout << "∞" << ' ';
                continue;
            }
            cout << weight[i][j] << ' ';
        }
        cout << endl;
    }
    /*cout<<endl<<"经过顶点3进行中转"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            weight[i][j]=min(weight[i][j],weight[i][3]+weight[3][j]);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(weight[i][j]==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<weight[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl<<"经过顶点3,4进行中转"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            weight[i][j]=min(weight[i][j],weight[i][3]+weight[3][j]);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            weight[i][j]=min(weight[i][j],weight[i][4]+weight[4][j]);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(weight[i][j]==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<weight[i][j]<<' ';
        }
        cout<<endl;
    }*/
    cout << endl << "结果" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {//在第i次循环中,weight数组中所有与i有关的值都不会改变
        for (int j = 1; j <= graph->_vertex; ++j) {
            for (int k = 1; k <= graph->_vertex; ++k) {
                if (weight[j][k] > weight[j][i] + weight[i][k]) {
                    weight[j][k] = weight[j][i] + weight[i][k];
                    path[j][k] = path[j][i];//将最短路径更新
                    /*解析
                    假定有1,2,3,4共四个点
                    1->2=5,2->3=6,3->4=7,共三条弧
                    以1为中转点时,最短路径无更新
                    以2为中转点时
                    1->3由INF转变为1->2 + 2->3 = 11
                    path[1][3]=path[1][2]=2
                    以3为中转点时
                    1->4由INF转变为1->3 + 3->4 = 18
                    path[1][4]=path[1][3]=path[1][2]=2
                    2->4由INF转变为2->3 + 3->4 = 13
                    path[2][4]=path[2][3]=3
                    打印 1->4 的最短路径
                    起点(start)为1,终点(end)为4
                    path[1][4]=2,输出2,问题转化为打印 2->4 的最短路径
                    path[2][4]=3,输出3,问题转化为打印 3->4 的最短路径
                    path[3][4]=4,输出4,问题转化为打印 4->4 的最短路径
                    4=4,结束
                    */
                }
            }
        }
    }
    for (int i = 1; i <= graph->_vertex; ++i) {
        for (int j = 1; j <= graph->_vertex; ++j) {
            if (weight[i][j] == INF) {
                cout << "∞" << ' ';
                continue;
            }
            cout << weight[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void print_path(M_G graph, int start, int end, int path[][_MAX]) {
    if (start == end) {
        cout << graph->vertex[start] << "->" << graph->vertex[end];
    }
    int i = start;
    cout << graph->vertex[i];
    while (i != end) {
        cout << "->";
        i = path[i][end];
        cout << graph->vertex[i];
    }
}

void print(M_G graph) {
    for (int i = 1; i <= graph->_vertex; ++i) {
        for (int j = 1; j <= graph->_vertex; ++j) {
            if (graph->Mar[i][j].weight == INF) {
                cout << "∞" << ' ';
                continue;
            }
            cout << graph->Mar[i][j].weight << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    M_G graph = nullptr;
    Create_Graph(graph);
    cout << "当前图的类型: ";
    switch (graph->kind) {
        case DN:
            cout << "带权有向图" << endl;
            break;
        case UDN:
            cout << "带权无向图" << endl;
            break;
    }
    cout << "邻接矩阵: " << endl;
    print(graph);
    int weight[_MAX][_MAX] = {0};
    int path[_MAX][_MAX] = {0};
    Floyd(graph, weight, path);
    for (int i = 1; i <= graph->_vertex; ++i) {
        for (int j = 1; j <= graph->_vertex; ++j) {
            print_path(graph, i, j, path);
            cout << ' ' << weight[i][j] << endl;
        }
    }
    delete graph;
    graph = nullptr;
    return 0;
}