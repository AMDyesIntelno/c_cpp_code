/*邻接表*/
#include<iostream>
#include<queue>

#define _MAX 21
using namespace std;
typedef enum {
    DG, DN, UDG, UDN
} Graphkind;//有向图,带权有向图,无向图,带权无向图
struct ARC {//记录弧
    int next_vertex;//记录当前弧的弧头,a->b,a->c,a->d,记录bcd
    int weight;
    struct ARC *next = nullptr;
};
typedef struct VERTEX {//记录顶点
    char data;//记录顶点的值
    ARC *node = nullptr;
} vertex[_MAX];
typedef struct AL_Graph {
    vertex v;
    Graphkind kind;//图的类型
    int _vertex, _arc;//顶点数量,弧数量
} *AL_G;
bool visited[_MAX] = {false};

inline int find(AL_G graph, char item) {//查找当前值对应的序号
    for (int i = 1; i <= graph->_vertex; ++i) {
        if (graph->v[i].data == item) {
            return i;
        }
    }
    return 0;
}

void Create_DG(AL_G &graph) {//创建有向图
    cout << "顶点数量: ";
    cin >> graph->_vertex;
    cout << "弧数量: ";
    cin >> graph->_arc;
    cout << "输入顶点的值:" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        cin >> graph->v[i].data;
    }
    ARC **node = new ARC *[graph->_vertex + 1];//标记某个节点的最后的一条弧
    for (int i = 1; i <= graph->_vertex; ++i) {
        node[i] = nullptr;
    }
    cout << "输入弧尾和弧头:" << endl;
    char v1, v2;//v1弧头,v2弧尾,即从v2指向v1,不带权
    for (int i = 1; i <= graph->_arc; ++i) {
        cin >> v2 >> v1;
        int posi1 = find(graph, v1);
        int posi2 = find(graph, v2);
        if (posi1 == 0 || posi2 == 0) {
            exit(-1);
        }
        if (node[posi2] == nullptr) {//第一个节点
            graph->v[posi2].node = new ARC;
            node[posi2] = graph->v[posi2].node;
            graph->v[posi2].node->next_vertex = posi1;
            graph->v[posi2].node->weight = 1;
        }
        else {
            node[posi2]->next = new ARC;
            node[posi2] = node[posi2]->next;
            node[posi2]->next_vertex = posi1;
            node[posi2]->weight = 1;
        }
    }
    delete[]node;
}

void Create_DN(AL_G &graph) {//创建带权有向图
    cout << "顶点数量: ";
    cin >> graph->_vertex;
    cout << "弧数量: ";
    cin >> graph->_arc;
    cout << "输入顶点的值:" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        cin >> graph->v[i].data;
    }
    ARC **node = new ARC *[graph->_vertex + 1];
    for (int i = 1; i <= graph->_vertex; ++i) {
        node[i] = nullptr;
    }
    cout << "输入弧尾,弧头和弧的权重:" << endl;
    char v1, v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    for (int i = 1; i <= graph->_arc; ++i) {
        cin >> v2 >> v1 >> weight;
        int posi1 = find(graph, v1);
        int posi2 = find(graph, v2);
        if (posi1 == 0 || posi2 == 0) {
            exit(-1);
        }
        if (node[posi2] == nullptr) {
            graph->v[posi2].node = new ARC;
            node[posi2] = graph->v[posi2].node;
            graph->v[posi2].node->next_vertex = posi1;
            graph->v[posi2].node->weight = weight;
        }
        else {
            node[posi2]->next = new ARC;
            node[posi2] = node[posi2]->next;
            node[posi2]->next_vertex = posi1;
            node[posi2]->weight = weight;
        }
    }
    delete[]node;
}

void Create_UDG(AL_G &graph) {//创建无向图
    cout << "顶点数量: ";
    cin >> graph->_vertex;
    cout << "弧数量: ";
    cin >> graph->_arc;
    cout << "输入顶点的值:" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        cin >> graph->v[i].data;
    }
    ARC **node = new ARC *[graph->_vertex + 1];
    for (int i = 1; i <= graph->_vertex; ++i) {
        node[i] = nullptr;
    }
    cout << "输入弧尾和弧头:" << endl;
    char v1, v2;//v1弧头,v2弧尾,即从v2指向v1,不带权
    for (int i = 1; i <= graph->_arc; ++i) {
        cin >> v2 >> v1;
        int posi1 = find(graph, v1);
        int posi2 = find(graph, v2);
        if (posi1 == 0 || posi2 == 0) {
            exit(-1);
        }
        if (node[posi2] == nullptr) {
            graph->v[posi2].node = new ARC;
            node[posi2] = graph->v[posi2].node;
            graph->v[posi2].node->next_vertex = posi1;
            graph->v[posi2].node->weight = 1;
        }
        else {
            node[posi2]->next = new ARC;
            node[posi2] = node[posi2]->next;
            node[posi2]->next_vertex = posi1;
            node[posi2]->weight = 1;
        }
        if (node[posi1] == nullptr) {
            graph->v[posi1].node = new ARC;
            node[posi1] = graph->v[posi1].node;
            graph->v[posi1].node->next_vertex = posi2;
            graph->v[posi1].node->weight = 1;
        }
        else {
            node[posi1]->next = new ARC;
            node[posi1] = node[posi1]->next;
            node[posi1]->next_vertex = posi2;
            node[posi1]->weight = 1;
        }
    }
    delete[]node;
}

void Create_UDN(AL_G &graph) {//创建带权无向图
    cout << "顶点数量: ";
    cin >> graph->_vertex;
    cout << "弧数量: ";
    cin >> graph->_arc;
    cout << "输入顶点的值:" << endl;
    for (int i = 1; i <= graph->_vertex; ++i) {
        cin >> graph->v[i].data;
    }
    ARC **node = new ARC *[graph->_vertex + 1];
    for (int i = 1; i <= graph->_vertex; ++i) {
        node[i] = nullptr;
    }
    cout << "输入弧尾,弧头和弧的权重:" << endl;
    char v1, v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    for (int i = 1; i <= graph->_arc; ++i) {
        cin >> v2 >> v1 >> weight;
        int posi1 = find(graph, v1);
        int posi2 = find(graph, v2);
        if (posi1 == 0 || posi2 == 0) {
            exit(-1);
        }
        if (node[posi2] == nullptr) {
            graph->v[posi2].node = new ARC;
            node[posi2] = graph->v[posi2].node;
            graph->v[posi2].node->next_vertex = posi1;
            graph->v[posi2].node->weight = weight;
        }
        else {
            node[posi2]->next = new ARC;
            node[posi2] = node[posi2]->next;
            node[posi2]->next_vertex = posi1;
            node[posi2]->weight = weight;
        }
        if (node[posi1] == nullptr) {
            graph->v[posi1].node = new ARC;
            node[posi1] = graph->v[posi1].node;
            graph->v[posi1].node->next_vertex = posi2;
            graph->v[posi1].node->weight = weight;
        }
        else {
            node[posi1]->next = new ARC;
            node[posi1] = node[posi1]->next;
            node[posi1]->next_vertex = posi2;
            node[posi1]->weight = weight;
        }
    }
    delete[]node;
}

void Create_Graph(AL_G &graph) {
    cout << "0:创建有向图 1:创建带权有向图 2:创建无向图 3:创建带权无向图" << endl;
    cout << "选项: ";
    graph = new AL_Graph;
    cin >> (int &) graph->kind;
    switch (graph->kind) {
        case DG:
            Create_DG(graph);
            break;
        case DN:
            Create_DN(graph);
            break;
        case UDG:
            Create_UDG(graph);
            break;
        case UDN:
            Create_UDN(graph);
            break;
        default:
            cout << "ERROR!" << endl;
            break;
    }
}

void Add_vertex(AL_G &graph, char item) {//添加一个顶点
    graph->_vertex++;
    graph->v[graph->_vertex].data = item;
}

void Add_arc(AL_G &graph, char v2, char v1, int weight = 1) {//添加一条弧,v1弧头,v2弧尾,即从v2指向v1,不带权的weight默认为1
    if (find(graph, v2) && find(graph, v1)) {
        ARC *now = graph->v[find(graph, v2)].node;
        ARC *prev = graph->v[find(graph, v2)].node;
        if (now == nullptr) {//还没有弧的情况
            graph->v[find(graph, v2)].node = new ARC;
            graph->v[find(graph, v2)].node->next_vertex = find(graph, v1);
            graph->v[find(graph, v2)].node->weight = weight;
        }
        else {
            while (now) {
                prev = now;
                now = now->next;
            }
            now = new ARC;
            now->next_vertex = find(graph, v1);
            now->weight = weight;
            prev->next = now;
        }
        if (graph->kind == UDG || graph->kind == UDN) {
            now = graph->v[find(graph, v1)].node;
            prev = graph->v[find(graph, v1)].node;
            if (now == nullptr) {
                graph->v[find(graph, v1)].node = new ARC;
                graph->v[find(graph, v1)].node->next_vertex = find(graph, v2);
                graph->v[find(graph, v1)].node->weight = weight;
            }
            else {
                while (now) {
                    prev = now;
                    now = now->next;
                }
                now = new ARC;
                now->next_vertex = find(graph, v2);
                now->weight = weight;
                prev->next = now;
            }
        }
        graph->_arc++;
    }
}

void Delete_arc(AL_G &graph, char v2, char v1) {//删除一条弧,v1弧头,v2弧尾,即从v2指向v1
    if (find(graph, v2) && find(graph, v1)) {
        ARC *prev = graph->v[find(graph, v2)].node;
        ARC *now = graph->v[find(graph, v2)].node;
        if (now && now->next_vertex == find(graph, v1)) {//第一条弧,特判
            graph->v[find(graph, v2)].node = now->next;
            delete now;
        }
        else {
            while (now && now->next_vertex != find(graph, v1)) {
                prev = now;
                now = now->next;
            }
            if (now && now->next_vertex == find(graph, v1)) {
                prev->next = now->next;
                delete now;
            }
            else {
                return;
            }
        }
        if (graph->kind == UDG || graph->kind == UDN) {
            prev = graph->v[find(graph, v1)].node;
            now = graph->v[find(graph, v1)].node;
            if (now && now->next_vertex == find(graph, v2)) {
                graph->v[find(graph, v1)].node = now->next;
                delete now;
            }
            else {
                while (now && now->next_vertex != find(graph, v2)) {
                    prev = now;
                    now = now->next;
                }
                if (now && now->next_vertex == find(graph, v2)) {
                    prev->next = now->next;
                    delete now;
                }
                else {
                    return;
                }
            }
        }
        graph->_arc--;
    }
}

void Delete_vertex(AL_G &graph, char item) {//删除一个顶点
    for (int i = 1; i <= graph->_vertex; ++i) {//删除所有弧尾为当前顶点的弧
        Delete_arc(graph, item, graph->v[i].data);
    }
    for (int i = 1; i <= graph->_vertex; ++i) {//删除所有弧头为当前顶点的弧
        Delete_arc(graph, graph->v[i].data, item);
    }
    for (int i = 1; i <= graph->_vertex; ++i) {//弧头的顶点的对应数值-1
        ARC *node = graph->v[i].node;
        while (node) {
            if (node->next_vertex > find(graph, item)) {
                node->next_vertex--;
            }
            node = node->next;
        }
    }
    delete graph->v[find(graph, item)].node;//清除当前顶点,并将后面的节点前移
    graph->v[find(graph, item)].node = nullptr;
    for (int i = find(graph, item); i < graph->_vertex; ++i) {
        graph->v[i] = graph->v[i + 1];
        graph->v[i + 1].node = nullptr;
    }
    graph->v[graph->_vertex].node = nullptr;
    graph->v[graph->_vertex].data = 0;
    --graph->_vertex;
}

int Fir_posi(AL_G graph, char item) {//返回与item链接的第一个邻接顶点序号,即与item链接的第一个弧头
    int posi = find(graph, item);
    if (posi) {
        if (graph->v[posi].node) {
            return graph->v[posi].node->next_vertex;
        }
    }
    return 0;
}

int Next_posi(AL_G graph, char item, char now) {//返回与item链接并且在now之后的顶点序号,即与item链接的其他弧头
    int posi1 = find(graph, item);
    int posi2 = find(graph, now);
    if (posi1 && posi2) {
        ARC *node = graph->v[posi1].node;
        while (node && node->next_vertex != posi2) {
            node = node->next;
        }
        if (node && node->next) {
            return node->next->next_vertex;
        }
    }
    return 0;
}

void DFS_core(AL_G graph, int posi) {
    visited[posi] = true;
    cout << graph->v[posi].data;
    for (int i = Fir_posi(graph, graph->v[posi].data); i > 0; i = Next_posi(graph, graph->v[posi].data, graph->v[i].data)) {
        if (!visited[i]) {
            DFS_core(graph, i);
        }
    }
}

void DFS(AL_G graph) {
    for (int i = 1; i <= graph->_vertex; ++i) {
        if (!visited[i]) {
            DFS_core(graph, i);
        }
    }
    cout << endl;
    fill(visited, visited + _MAX, 0);
}

void BFS(AL_G graph) {
    fill(visited, visited + _MAX, 0);
    queue<int> q;
    for (int i = 1; i <= graph->_vertex; ++i) {
        if (!visited[i]) {
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int temp = q.front();
                q.pop();
                cout << graph->v[temp].data;
                ARC *node = graph->v[temp].node;
                while (node) {
                    if (!visited[node->next_vertex]) {
                        q.push(node->next_vertex);
                        visited[node->next_vertex] = true;
                    }
                    node = node->next;
                }
            }
        }
    }
    cout << endl;
    fill(visited, visited + _MAX, 0);
}

void print(AL_G graph) {
    if (graph->kind == DG || graph->kind == UDG) {
        for (int i = 1; i <= graph->_vertex; ++i) {
            ARC *node = graph->v[i].node;
            cout << graph->v[i].data << ": ";
            if (node) {
                while (node) {
                    cout << graph->v[i].data << "->" << graph->v[node->next_vertex].data << ' ';
                    node = node->next;
                }
                cout << endl;
            }
            else {
                cout << "\\" << endl;
            }
        }
    }
    else {
        for (int i = 1; i <= graph->_vertex; ++i) {
            ARC *node = graph->v[i].node;
            cout << graph->v[i].data << ": ";
            if (node) {
                while (node) {
                    cout << graph->v[i].data << "-" << node->weight << "->" << graph->v[node->next_vertex].data << ' ';
                    node = node->next;
                }
                cout << endl;
            }
            else {
                cout << "\\" << endl;
            }
        }
    }
}

int main() {
    AL_G graph = nullptr;
    Create_Graph(graph);
    cout << "当前图的类型: ";
    switch (graph->kind) {
        case DG:
            cout << "有向图" << endl;
            break;
        case DN:
            cout << "带权有向图" << endl;
            break;
        case UDG:
            cout << "无向图" << endl;
            break;
        case UDN:
            cout << "带权无向图" << endl;
            break;
    }
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "删除顶点b" << endl;
    Delete_vertex(graph, 'b');
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "删除顶点a" << endl;
    Delete_vertex(graph, 'a');
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "删除弧d->f" << endl;
    Delete_arc(graph, 'd', 'f');
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "删除弧d->c" << endl;
    Delete_arc(graph, 'd', 'c');
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "添加顶点g" << endl;
    Add_vertex(graph, 'g');
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "添加弧g->c";
    if (graph->kind == DG || graph->kind == UDG) {
        cout << endl;
        Add_arc(graph, 'g', 'c');
    }
    else {
        cout << " weight:6" << endl;
        Add_arc(graph, 'g', 'c', 6);
    }
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    cout << "----------------" << endl;
    cout << "添加弧e->g";
    if (graph->kind == DG || graph->kind == UDG) {
        cout << endl;
        Add_arc(graph, 'e', 'g');
    }
    else {
        cout << " weight:7" << endl;
        Add_arc(graph, 'e', 'g', 7);
    }
    cout << "邻接表: " << endl;
    print(graph);
    cout << "DFS: ";
    DFS(graph);
    cout << "BFS: ";
    BFS(graph);
    delete graph;
    graph = nullptr;
    return 0;
}