#include<iostream>
#include<stack>
#include<queue>

using namespace std;
typedef struct Tree {
    char data = '\0';
    struct Tree *left = nullptr;
    struct Tree *right = nullptr;
} *tree;

void Create_tree(tree &t) {//以先序次序创建树,以空格代表空结点
    char temp;
    temp = getchar();
    t = new Tree;
    if (temp != '\n') {
        if (temp == ' ') {
            delete t;
            t = nullptr;
        }
        else {
            t->data = temp;
            Create_tree(t->left);
            Create_tree(t->right);
        }
    }
}

void Clear_tree(tree &t) {//清空树
    if (t) {
        Clear_tree(t->left);
        Clear_tree(t->right);
        delete t;
        t = nullptr;
    }
}

bool IsEmpty_tree(tree t) {//检查树是否为空
    return t == nullptr;
}

int Depth_tree(tree t) {//树的深度
    return t == nullptr ? 0 : Depth_tree(t->left) + Depth_tree(t->right) + 1;
}

int Number_of_nodes(tree t) {//结点数量
    return t == nullptr ? 0 : Depth_tree(t->left) + Depth_tree(t->right) + 2;
}

void Preorder_traversal(tree t) {//先序遍历(递归)
    if (t) {
        cout << t->data;
        Preorder_traversal(t->left);
        Preorder_traversal(t->right);
    }
}

void Inorder_traversal(tree t) {//中序遍历(递归)
    if (t) {
        Inorder_traversal(t->left);
        cout << t->data;
        Inorder_traversal(t->right);
    }
}

void Postorder_traversal(tree t) {//后序遍历(递归)
    if (t) {
        Postorder_traversal(t->left);
        Postorder_traversal(t->right);
        cout << t->data;
    }
}

void Preorder_traversal_non_recursive(tree t) {//先序遍历(非递归)
    if (t) {
        stack<tree> s;
        s.push(t);
        t = t->left;
        cout << s.top()->data;
        while (t || (!s.empty())) {
            while (t) {//沿着左子树搜素,将非空节点进栈并输出
                s.push(t);
                cout << s.top()->data;
                t = t->left;
            }
            while (!s.empty() && s.top()->right == nullptr) {//当没有右子树时节点退栈
                s.pop();
            }
            if (!s.empty()) {//当有右子树时,进入右子树,节点退栈
                t = s.top()->right;
                s.pop();
            }
        }
    }
}

void Inorder_traversal_non_recursive(tree t) {//中序遍历(非递归)
    if (t) {
        stack<tree> s;
        s.push(t);
        t = t->left;
        while (t || (!s.empty())) {
            while (t) {//沿着左子树搜素,将非空节点进栈
                s.push(t);
                t = t->left;
            }
            while (!s.empty() && s.top()->right == nullptr) {//当没有右子树时节点退栈并输出
                cout << s.top()->data;
                s.pop();
            }
            if (!s.empty()) {//当有右子树时,进入右子树,原节点退栈并输出
                cout << s.top()->data;
                t = s.top()->right;
                s.pop();
            }
        }
    }
}

void Postorder_traversal_non_recursive(tree t) {//后序遍历(非递归)
    if (t) {
        stack<tree> s;
        stack<tree> root;//根栈,保存根节点
        s.push(t);
        t = t->left;
        while (t || (!s.empty())) {
            while (t) {//沿着左子树搜素,将非空节点进栈
                s.push(t);
                t = t->left;
            }
            while (!s.empty() && s.top()->right == nullptr) {//当没有右子树时节点退栈并输出
                cout << s.top()->data;
                if (!root.empty() && s.top() == root.top()) {//当该节点为根节点时,弹出根栈,即该节点没有右子树
                    root.pop();
                }
                s.pop();
            }
            while (!s.empty() && (!root.empty()) && s.top() == root.top()) {//当节点再次等于根节点时,节点退栈并输出
                cout << s.top()->data;
                s.pop();
                root.pop();
            }
            if (!s.empty()) {
                root.push(s.top());//当有右子树时,进入右子树,原节点作为根节点进入根栈
                t = s.top()->right;
            }
        }
    }
}

void Levelorder_traversal(tree t) {//层序遍历
    if (t) {
        queue<tree> q;//借助队列手动模拟层序遍历
        int depth = Depth_tree(t);
        q.push(t);
        while (depth > 0) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                cout << q.front()->data;
                if (q.front()->left) {
                    q.push(q.front()->left);
                }
                if (q.front()->right) {
                    q.push(q.front()->right);
                }
                q.pop();
            }
            --depth;
        }
    }
}

char Get_left_child(tree t, char posi) {//获取某个结点的左孩子结点
    if (t) {
        queue<tree> q;//借助队列手动模拟
        int depth = Depth_tree(t);
        q.push(t);
        while (depth > 0) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                if (q.front()->data == posi) {
                    if (q.front()->left == nullptr) {
                        return '\0';
                    }
                    else {
                        return q.front()->left->data;
                    }
                }
                if (q.front()->left) {
                    q.push(q.front()->left);
                }
                if (q.front()->right) {
                    q.push(q.front()->right);
                }
                q.pop();
            }
            --depth;
        }
    }
    return '\0';
}

char Get_right_child(tree t, char posi) {//获取某个结点的右孩子结点
    if (t) {
        queue<tree> q;//借助队列手动模拟
        int depth = Depth_tree(t);
        q.push(t);
        while (depth > 0) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                if (q.front()->data == posi) {
                    if (q.front()->right == nullptr) {
                        return '\0';
                    }
                    else {
                        return q.front()->right->data;
                    }
                }
                if (q.front()->left) {
                    q.push(q.front()->left);
                }
                if (q.front()->right) {
                    q.push(q.front()->right);
                }
                q.pop();
            }
            --depth;
        }
    }
    return '\0';
}

char Get_root(tree t, char posi) {//获取某个结点的根结点
    if (t) {
        queue<tree> q;//借助队列手动模拟
        int depth = Depth_tree(t);
        q.push(t);
        while (depth > 0) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                if (q.front()->left && q.front()->left->data == posi) {
                    return q.front()->data;
                }
                if (q.front()->right && q.front()->right->data == posi) {
                    return q.front()->data;
                }
                if (q.front()->left) {
                    q.push(q.front()->left);
                }
                if (q.front()->right) {
                    q.push(q.front()->right);
                }
                q.pop();
            }
            --depth;
        }
    }
    return '\0';
}

char Get_left_brother(tree t, char posi) {//获取某个结点的左兄弟结点
    if (Get_root(t, posi) == '\0') {
        return '\0';
    }
    return Get_left_child(t, Get_root(t, posi));
}

char Get_right_brother(tree t, char posi) {//获取某个结点的右兄弟结点
    if (Get_root(t, posi) == '\0') {
        return '\0';
    }
    return Get_right_child(t, Get_root(t, posi));
}

void Exchange(tree &t) {//交换左右子树
    if (t) {
        swap(t->left, t->right);
        Exchange(t->left);
        Exchange(t->right);
    }
}

int main() {
    tree t = nullptr;
    Create_tree(t);
    IsEmpty_tree(t) ? cout << "Empty" << endl : cout << "Not_empty" << endl;
    cout << "Depth: " << Depth_tree(t) << endl;
    cout << "Number_of_nodes " << Number_of_nodes(t) << endl;
    cout << "Preorder_traversal: ";
    Preorder_traversal(t);
    cout << endl;
    cout << "_Preorder_traversal: ";
    Preorder_traversal_non_recursive(t);
    cout << endl;
    cout << "Inorder_traversal: ";
    Inorder_traversal(t);
    cout << endl;
    cout << "_Inorder_traversal: ";
    Inorder_traversal_non_recursive(t);
    cout << endl;
    cout << "Postorder_traversal: ";
    Postorder_traversal(t);
    cout << endl;
    cout << "_Postorder_traversal: ";
    Postorder_traversal_non_recursive(t);
    cout << endl;
    cout << "Levelorder_traversal: ";
    Levelorder_traversal(t);
    cout << endl;
    char temp = t->left->data;
    cout << "Current_node: " << temp << endl;
    cout << "Left_child: ";
    Get_left_child(t, temp) == '\0' ? cout << "NULL!" << endl : cout << Get_left_child(t, temp) << endl;
    cout << "Right_child: ";
    Get_right_child(t, temp) == '\0' ? cout << "NULL!" << endl : cout << Get_right_child(t, temp) << endl;
    cout << "Root_node: " << Get_root(t, temp) << endl;
    cout << "Left_brother: ";
    (Get_left_brother(t, temp) == temp || Get_left_brother(t, temp) == '\0') ? cout << "NULL!" << endl : cout << Get_left_brother(t, temp) << endl;
    cout << "Right_brother: ";
    (Get_right_brother(t, temp) == temp || Get_right_brother(t, temp) == '\0') ? cout << "NULL!" << endl : cout << Get_right_brother(t, temp) << endl;
    cout << "Exchange..." << endl;
    Exchange(t);
    cout << "Levelorder_traversal: ";
    Levelorder_traversal(t);
    cout << endl;
    Clear_tree(t);
    return 0;
}