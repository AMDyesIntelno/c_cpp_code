#include<iostream>
#include<stack>

using namespace std;
enum pointtag {
    Link,//0
    Thread//1
};
typedef struct Tree {
    char data = '\0';
    struct Tree *left = nullptr;
    struct Tree *right = nullptr;
    pointtag left_Tag, right_Tag;
} *tree;
tree pre = nullptr;//指向前一个访问过的结点
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
            if (t->left) {//有实际节点就设置为Link
                t->left_Tag = Link;
            }
            else {
                t->left_Tag = Thread;
            }
            Create_tree(t->right);
            if (t->right) {//有实际节点就设置为Link
                t->right_Tag = Link;
            }
            else {
                t->right_Tag = Thread;
            }
        }
    }
}

void Clear_Thread(tree &t) {//清除前一次线索化所产生的线索
    if (t) {
        if (t->left_Tag == Thread) {
            t->left = nullptr;
        }
        if (t->right_Tag == Thread) {
            t->right = nullptr;
        }
        Clear_Thread(t->left);
        Clear_Thread(t->right);
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

void Preorder_Thread(tree t) {//先序线索化
    if (t) {
        if (!t->left) {
            t->left_Tag = Thread;
            t->left = pre;
        }
        if (pre && !pre->right) {
            pre->right_Tag = Thread;
            pre->right = t;
        }
        pre = t;
        if (t->left_Tag == Link) {
            Preorder_Thread(t->left);
        }
        if (t->right_Tag == Link) {
            Preorder_Thread(t->right);
        }
    }
}

void Inorder_Thread(tree t) {//中序线索化
    if (t) {
        if (t->left_Tag == Link) {
            Inorder_Thread(t->left);
        }
        if (!t->left) {
            t->left_Tag = Thread;
            t->left = pre;
        }
        if (pre && !pre->right) {
            pre->right_Tag = Thread;
            pre->right = t;
        }
        pre = t;
        if (t->right_Tag == Link) {
            Inorder_Thread(t->right);
        }
    }
}

void Postorder_Thread(tree t) {//后序线索化
    if (t) {
        if (t->left_Tag == Link) {
            Postorder_Thread(t->left);
        }
        if (t->right_Tag == Link) {
            Postorder_Thread(t->right);
        }
        if (!t->left) {
            t->left_Tag = Thread;
            t->left = pre;
        }
        if (pre && !pre->right) {
            pre->right_Tag = Thread;
            pre->right = t;
        }
        pre = t;
    }
}

void Preorder_traversal(tree t) {//先序遍历并先序线索化
    if (t) {
        pre = nullptr;
        Preorder_Thread(t);
    }
}

void Inorder_traversal(tree t) {//中序遍历并中序线索化
    if (t) {
        pre = nullptr;
        Inorder_Thread(t);
    }
}

void Postorder_traversal(tree t) {//后序遍历并后序线索化
    if (t) {
        pre = nullptr;
        Postorder_Thread(t);
    }
}

void Preorder_traversal_core(tree t) {//借助先序线索化遍历二叉树
    if (t) {
        while (t) {
            while (t->left_Tag == Link) {//直到最左边的节点
                cout << t->data;
                t = t->left;
            }
            cout << t->data;
            t = t->right;
            //如果最左边的节点有直接右子树,那么进入该右子树
            //如果最左边的节点的右节点是线索形式,那么直接到达当前节点的后继节点,继续开始左子树的遍历
        }
    }
}

void Inorder_traversal_core(tree t) {//借助中序线索化遍历二叉树
    if (t) {
        while (t) {
            while (t->left_Tag == Link) {//先遍历左子树到底
                t = t->left;
            }
            cout << t->data;
            if (t->right_Tag == Link) {//如果当前节点的右子树是直接右子树,那么进入该右子树
                t = t->right;
            }
            else {//如果当前的节点的右节点是线索形式,那么直接转到当前节点的后继节点,直到当前节点为空,或者有新的右子树可以进入
                while (t && t->right_Tag == Thread) {
                    t = t->right;
                    if (t) {
                        cout << t->data;
                    }
                }
                if (t) {//进入新的右子树,再次开始遍历
                    t = t->right;
                }
            }
        }
    }
}

void Postorder_traversal_core(tree t) {//借助后序线索化遍历二叉树
    if (t) {
        stack<tree> s;
        //如果在定义二叉树时,没有定义父节点(二叉链表形式),那么使用栈来进行回溯
        //如果有定义(三叉链表形式),那么直接使用父节点
        tree prev = nullptr;//前一个节点,用于判断当前节点是否已经遍历完成
        while (t) {
            while (t->left_Tag == Link && t->left != prev) {//遍历左子树到底,并且避免出现重复遍历的情况
                if (t->right_Tag == Link || t->left->right_Tag == Link) {//当前节点存在右子树或者无法通过后继节点指向当前节点时,节点进栈
                    s.push(t);
                }
                t = t->left;
            }
            while (t && t->right_Tag == Thread) {//当前节点的右节点为线索节点,那么进入右节点直接转到当前节点的后继节点,直到存在右子树或当前节点为空
                cout << t->data;
                prev = t;
                t = t->right;
            }
            while (t && t->right == prev) {//判断当前右子树是否已经遍历
                //如果prev是当前节点的右节点,那么说明当前右子树已经遍历
                //那么取一个与当前节点不同的新节点,判断能否进入
                //如果不是,那么说明当前右子树没有被遍历
                cout << t->data;
                prev = t;
                if (!s.empty()) {
                    if (t == s.top()) {//栈顶节点与当前节点相同,直接弹出栈顶节点
                        s.pop();
                    }
                    if (!s.empty()) {//如果不同,取栈顶节点并弹出
                        t = s.top();
                        s.pop();
                    }
                    else {
                        t = nullptr;
                    }
                }
                else {
                    t = nullptr;
                }
            }
            if (t && t->right_Tag == Link) {//进入右子树,并将当前节点入栈,作为根节点
                s.push(t);
                t = t->right;
            }
        }
    }
}

int main() {
    tree t = nullptr;
    Create_tree(t);
    cout << "Preorder_traversal: ";
    Preorder_traversal(t);
    Preorder_traversal_core(t);
    cout << endl;
    Clear_Thread(t);
    cout << "Inorder_traversal: ";
    Inorder_traversal(t);
    Inorder_traversal_core(t);
    cout << endl;
    Clear_Thread(t);
    cout << "Postorder_traversal: ";
    Postorder_traversal(t);
    Postorder_traversal_core(t);
    Clear_Thread(t);
    Clear_tree(t);
    return 0;
}