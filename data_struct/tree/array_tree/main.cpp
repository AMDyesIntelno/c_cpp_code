#include<iostream>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<cstdlib>

#define MAX_SIZE 100
using namespace std;

void Init_tree(char *t) {//初始化
    for (int i = 0; i < MAX_SIZE; ++i) {
        t[i] = 0;
    }
}

void Create_tree(char *t) {//创建树,以空格代表空结点,输入顺序为层序遍历
    char temp;
    int i = 0;
    temp = getchar();
    while (temp != '\n') {
        if (temp == ' ') {
            t[i++] = '\0';
        }
        else {
            t[i++] = temp;
        }
        temp = getchar();
    }
}

bool IsEmpty_tree(const char *t) {//检查树是否为空
    return t[0] == 0;
}

int Length_tree(const char *t) {//树的长度
    int l = MAX_SIZE - 1;
    for (l; l >= 0; --l) {
        if (t[l] != '\0') {
            break;
        }
    }
    return l + 1;
}

int Depth_tree(char *t) {//树的深度
    int d = 1;
    while ((pow(2, d) - 1) < Length_tree(t)) {
        ++d;
    }
    return d;
}

int Number_of_nodes(const char *t) {//结点数量
    int n = 0;
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (t[i] != '\0') {
            ++n;
        }
    }
    return n;
}

void Preorder_traversal(char *t, int posi) {//先序遍历(递归)
    if (t[posi]) {
        cout << t[posi];
        Preorder_traversal(t, 2 * posi + 1);
        Preorder_traversal(t, 2 * (posi + 1));
    }
}

void Inorder_traversal(char *t, int posi) {//中序遍历(递归)
    if (t[posi]) {
        Inorder_traversal(t, 2 * posi + 1);
        cout << t[posi];
        Inorder_traversal(t, 2 * (posi + 1));
    }
}

void Postorder_traversal(char *t, int posi) {//后序遍历(递归)
    if (t[posi]) {
        Postorder_traversal(t, 2 * posi + 1);
        Postorder_traversal(t, 2 * (posi + 1));
        cout << t[posi];
    }
}

void Levelorder_traversal(char *t) {//层序遍历
    for (int i = 0; i < MAX_SIZE; ++i) {
        cout << t[i];
    }
}

void Preorder_traversal_non_recursive(char *t) {//先序遍历(非递归)
    int posi = 0;
    if (t[posi]) {
        stack<int> s;
        s.push(posi);
        posi = 2 * posi + 1;
        cout << t[s.top()];
        while (t[posi] || (!s.empty())) {
            while (t[posi]) {//沿着左子树搜素,将非空节点进栈并输出
                s.push(posi);
                cout << t[s.top()];
                posi = 2 * posi + 1;
            }
            while (!s.empty() && t[2 * (s.top() + 1)] == '\0') {//当没有右子树时节点退栈
                s.pop();
            }
            if (!s.empty()) {//当有右子树时,进入右子树,节点退栈
                posi = 2 * (s.top() + 1);
                s.pop();
            }
        }
    }
}

void Inorder_traversal_non_recursive(char *t) {//中序遍历(非递归)
    int posi = 0;
    if (t[posi]) {
        stack<int> s;
        s.push(posi);
        posi = 2 * posi + 1;
        while (t[posi] || (!s.empty())) {
            while (t[posi]) {//沿着左子树搜素,将非空节点进栈
                s.push(posi);
                posi = 2 * posi + 1;
            }
            while (!s.empty() && t[2 * (s.top() + 1)] == '\0') {//当没有右子树时节点退栈并输出
                cout << t[s.top()];
                s.pop();
            }
            if (!s.empty()) {//当有右子树时,进入右子树,原节点退栈并输出
                cout << t[s.top()];
                posi = 2 * (s.top() + 1);
                s.pop();
            }
        }
    }
}

void Postorder_traversal_non_recursive(char *t) {//后序遍历(非递归)
    int posi = 0;
    if (t[posi]) {
        stack<int> s;
        stack<int> root;//根栈,保存根节点
        s.push(posi);
        posi = 2 * posi + 1;
        while (t[posi] || (!s.empty())) {
            while (t[posi]) {//沿着左子树搜素,将非空节点进栈
                s.push(posi);
                posi = 2 * posi + 1;
            }
            while (!s.empty() && t[2 * (s.top() + 1)] == '\0') {//当没有右子树时节点退栈并输出
                cout << t[s.top()];
                if (!root.empty() && s.top() == root.top()) {//当该节点为根节点时,弹出根栈,即该节点没有右子树
                    root.pop();
                }
                s.pop();
            }
            while (!s.empty() && (!root.empty()) && s.top() == root.top()) {//当节点再次等于根节点时,节点退栈并输出
                cout << t[s.top()];
                s.pop();
                root.pop();
            }
            if (!s.empty()) {
                root.push(s.top());//当有右子树时,进入右子树,原节点作为根节点进入根栈
                posi = 2 * (s.top() + 1);
            }
        }
    }
}

char Get_left_child(char *t, char posi) {//获取某个结点的左孩子结点
    int i = 0;
    for (; i < MAX_SIZE; ++i) {
        if (t[i] == posi) {
            break;
        }
    }
    if (2 * i + 1 < MAX_SIZE) {
        return t[2 * i + 1];
    }
    else {
        return '\0';
    }
}

char Get_right_child(char *t, char posi) {//获取某个结点的右孩子结点
    int i = 0;
    for (; i < MAX_SIZE; ++i) {
        if (t[i] == posi) {
            break;
        }
    }
    if (2 * (i + 1) < MAX_SIZE) {
        return t[2 * (i + 1)];
    }
    else {
        return '\0';
    }
}

char Get_root(char *t, char posi) {//获取某个结点的根结点
    int i = 0;
    for (; i < MAX_SIZE; ++i) {
        if (t[i] == posi) {
            break;
        }
    }
    int root = i % 2 == 1 ? (i - 1) / 2 : (i - 2) / 2;
    if (root < 0) {
        return '\0';
    }
    else if (root == 0) {
        return t[0];
    }
    else {
        return t[root];
    }
}

char Get_left_brother(char *t, char posi) {//获取某个结点的左兄弟结点
    if (Get_root(t, posi) == '\0') {
        return '\0';
    }
    return Get_left_child(t, Get_root(t, posi));
}

char Get_right_brother(char *t, char posi) {//获取某个结点的右兄弟结点
    if (Get_root(t, posi) == '\0') {
        return '\0';
    }
    return Get_right_child(t, Get_root(t, posi));
}

void Exchange(char *t, char *ex_t) {//交换左右子树,对二叉树的每一层进行层序遍历
    int depth = Depth_tree(t);
    int i = 0;
    queue<int> q;
    q.push(i);
    while (depth > 0) {
        int size = q.size();
        for (int j = 0; j < size; ++j) {
            ex_t[i++] = t[q.front()];
            q.push(2 * (q.front() + 1));
            q.push(2 * q.front() + 1);
            q.pop();
        }
        --depth;
    }
}

int main() {
    srand(time(nullptr));
    char tree[MAX_SIZE];
    Init_tree(tree);
    Create_tree(tree);
    IsEmpty_tree(tree) ? cout << "Empty" << endl : cout << "Not_empty" << endl;
    cout << "Depth: " << Depth_tree(tree) << endl;
    cout << "Length: " << Length_tree(tree) << endl;
    cout << "Number_of_nodes " << Number_of_nodes(tree) << endl;
    cout << "Preorder_traversal: ";
    Preorder_traversal(tree, 0);
    cout << endl;
    cout << "_Preorder_traversal: ";
    Preorder_traversal_non_recursive(tree);
    cout << endl;
    cout << "Inorder_traversal: ";
    Inorder_traversal(tree, 0);
    cout << endl;
    cout << "_Inorder_traversal: ";
    Inorder_traversal_non_recursive(tree);
    cout << endl;
    cout << "Postorder_traversal: ";
    Postorder_traversal(tree, 0);
    cout << endl;
    cout << "_Postorder_traversal: ";
    Postorder_traversal_non_recursive(tree);
    cout << endl;
    cout << "Levelorder_traversal: ";
    Levelorder_traversal(tree);
    cout << endl;
    char temp = tree[rand() % Length_tree(tree)];
    while (temp == '\0') {
        temp = tree[rand() % Length_tree(tree)];
    }
    cout << "Current_node: " << temp << endl;
    cout << "Left_child: ";
    Get_left_child(tree, temp) == '\0' ? cout << "NULL!" << endl : cout << Get_left_child(tree, temp) << endl;
    cout << "Right_child: ";
    Get_right_child(tree, temp) == '\0' ? cout << "NULL!" << endl : cout << Get_right_child(tree, temp) << endl;
    cout << "Root_node: ";
    Get_root(tree, temp) == '\0' ? cout << "NULL!" << endl : cout << Get_root(tree, temp) << endl;
    cout << "Left_brother: ";
    (Get_left_brother(tree, temp) == temp || Get_left_brother(tree, temp) == '\0') ? cout << "NULL!" << endl : cout << Get_left_brother(tree, temp) << endl;
    cout << "Right_brother: ";
    (Get_right_brother(tree, temp) == temp || Get_right_brother(tree, temp) == '\0') ? cout << "NULL!" << endl : cout << Get_right_brother(tree, temp) << endl;
    cout << "Exchange..." << endl;
    char ex_tree[MAX_SIZE] = {0};
    Exchange(tree, ex_tree);
    cout << "Levelorder_traversal: ";
    Levelorder_traversal(ex_tree);
    cout << endl;
    return 0;
}