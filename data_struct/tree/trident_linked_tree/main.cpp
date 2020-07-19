#include<iostream>
#include<queue>

using namespace std;
typedef struct Tree {
    char data = '\0';
    struct Tree *left = nullptr;
    struct Tree *right = nullptr;
    struct Tree *root = nullptr;
} *tree;

void Create_tree(tree &t, tree root) {//以先序次序创建树,以空格代表空结点
    char temp;
    temp = getchar();
    t = new Tree;
    if (temp != '\n') {
        if (temp == ' ') {
            delete t;
            t = nullptr;
        }
        else {
            if (t != root) {
                t->root = root;
            }
            t->data = temp;
            Create_tree(t->left, t);
            Create_tree(t->right, t);
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
    return t == nullptr ? 0 : max(Depth_tree(t->left), Depth_tree(t->right)) + 1;
}

int Number_of_nodes(tree t) {//结点数量
    return t == nullptr ? 0 : max(Depth_tree(t->left), Depth_tree(t->right)) + 2;
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
        tree temp = t;
        while (t) {
            cout << t->data;
            if (t->left) {//沿着左子树搜素,直到左子树为空
                t = t->left;
            }
            else if (t->right) {//当左子树为空时,尝试沿着右子树搜索
                t = t->right;
            }
            else {//回溯
                while (t && (t->right == nullptr || t->right == temp)) {//检查能否进入右子树,并排除已经进入过的情况,避免死循环
                    temp = t;
                    t = t->root;
                }
                if (t) {//进入右子树
                    t = t->right;
                }
            }
        }
    }
}

void Inorder_traversal_non_recursive(tree t) {//中序遍历(非递归)
    if (t) {
        tree temp = t;
        while (t) {
            if (t->left) {//沿着左子树搜素,直到左子树为空
                t = t->left;
            }
            else if (t->right) {//当左子树为空时,尝试沿着右子树搜索
                cout << t->data;
                t = t->right;
            }
            else {//回溯
                while (t && (t->right == nullptr || t->right == temp)) {//检查能否进入右子树,并排除已经进入过的情况,避免死循环
                    if (t->right != temp) {//排除已经进入过的情况,不再对其进行输出
                        cout << t->data;
                    }
                    temp = t;
                    t = t->root;
                }
                if (t) {//进入右子树,并输出当前根节点
                    cout << t->data;
                    t = t->right;
                }
            }
        }
    }
}

void Postorder_traversal_non_recursive(tree t) {//后序遍历(非递归)
    if (t) {
        tree temp = t;
        while (t) {
            if (t->left) {//沿着左子树搜素,直到左子树为空
                t = t->left;
            }
            else if (t->right) {//当左子树为空时,尝试沿着右子树搜索
                t = t->right;
            }
            else {//回溯
                while (t && (t->right == nullptr || t->right == temp)) {//检查能否进入右子树,并排除已经进入过的情况,避免死循环
                    cout << t->data;//在回溯时输出当前节点,即根节点
                    temp = t;
                    t = t->root;
                }
                if (t) {//进入右子树
                    t = t->right;
                }
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
    Create_tree(t, t);
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