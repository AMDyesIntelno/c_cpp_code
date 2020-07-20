#include<iostream>

using namespace std;
typedef struct AVL_Tree {
    int data;
    int height;
    struct AVL_Tree *left = nullptr;
    struct AVL_Tree *right = nullptr;
} *AVL;

inline int Get_Height(AVL tree) {
    if (tree == nullptr) {
        return 0;
    }
    return tree->height;
}

inline int Get_Balance(AVL tree) {
    if (tree == nullptr) {
        return 0;
    }
    return Get_Height(tree->left) - Get_Height(tree->right);
}

inline void Right_Rotate(AVL &tree) {
    AVL left_son = tree->left;
    AVL right_grand_son = left_son->right;
    left_son->right = tree;
    //根节点弯下来
    tree->left = right_grand_son;
    //right_grand_son节点接到弯下来的根节点的左子树(原本的左子树指向了left_son节点,弯下来后左子树空了出来)
    tree->height = max(Get_Height(tree->left), Get_Height(tree->right)) + 1;
    left_son->height = max(Get_Height(left_son->left), Get_Height(left_son->right)) + 1;
    //重新调整tree节点和left_son节点的高度,+1是因为还要计算自身
    tree = left_son;
    //替换根节点
}

inline void Left_Rotate(AVL &tree) {
    AVL right_son = tree->right;
    AVL left_grand_son = right_son->left;
    right_son->left = tree;
    //根节点弯下来
    tree->right = left_grand_son;
    //left_grand_son节点接到弯下来的根节点的右子树(原本的右子树指向了right_son节点,弯下来后右子树空了出来)
    tree->height = max(Get_Height(tree->left), Get_Height(tree->right)) + 1;
    right_son->height = max(Get_Height(right_son->left), Get_Height(right_son->right)) + 1;
    //重新调整tree节点和right_son节点的高度,+1是因为还要计算自身
    tree = right_son;
    //替换根节点
}

void Rotate(AVL &tree, int data) {//平衡修正
    tree->height = max(Get_Height(tree->left), Get_Height(tree->right)) + 1;
    int balance = Get_Balance(tree);
    if (balance > 1 && data < tree->left->data) {//left(由balance>1推导)-left(由data<tree->left->data推导),仅需进行一次右旋
        Right_Rotate(tree);
    }
    else if (balance < -1 && data > tree->right->data) {//right(由balance<-1推导)-right(由data>tree->right->data推导),仅需进行一次左旋
        Left_Rotate(tree);
    }
    else if (balance > 1 && data > tree->left->data) {//left(由balance>1推导)-right(由data>tree->left->data推导),先对tree-left进行一次左旋,然后对tree进行一次右旋
        Left_Rotate(tree->left);
        Right_Rotate(tree);
    }
    else if (balance < -1 && data < tree->right->data) {//right(balance<-1)-left(由data<tree->right->data推导),先对tree-right进行一次右旋,然后对tree进行一次左旋
        Right_Rotate(tree->right);
        Left_Rotate(tree);
    }
}

void AVL_Insert(AVL &tree, int data) {
    if (tree == nullptr) {
        tree = new AVL_Tree;
        tree->data = data;
        tree->height = 1;
    }
    else if (tree->data == data) {
    }
    if (data < tree->data) {
        AVL_Insert(tree->left, data);
    }
    else if (data > tree->data) {
        AVL_Insert(tree->right, data);
    }
    Rotate(tree, data);
}

void Delete(AVL &tree) {
    AVL now = nullptr, next = nullptr;
    if (tree->left == nullptr && tree->right == nullptr) {
        delete tree;
        tree = nullptr;
    }
    else if (tree->left == nullptr) {//左子树为空,仅需要调整右子树
        now = tree->right;
        tree->data = now->data;
        tree->left = now->left;
        tree->right = now->right;
        delete now;
        now = nullptr;
    }
    else if (tree->right == nullptr) {//右子树为空,仅需要调整左子树
        now = tree->left;
        tree->data = now->data;
        tree->left = now->left;
        tree->right = now->right;
        delete now;
        now = nullptr;
    }
    else {//保证中序遍历的顺序不会发生改变
        /*本质上不是删除原节点,而是修改原节点的值
        并修改某些节点的左右子树的指向以达到删除原节点的效果*/
        now = tree;
        next = tree->left;
        while (next->right) {
            //原节点的右子树接在左子树的最右端来保持中序遍历的顺序不变
            now = next;
            next = next->right;
        }
        tree->data = next->data;
        //修改原节点的值为左子树的最右端的值
        //以达到将原节点的右子树应该接在左子树的最右端来保持中序遍历的顺序不变的效果
        if (now != tree) {
            //当左子树含有右节点,将右节点替换为右节点的左子树,右节点的值由原节点记录
            //达到了'删除'原节点并保持中序遍历顺序不变的效果
            now->right = next->left;
        }
        else {
            //当左子树不包含右节点,将原节点的左子树替换为左节点的左子树,左节点的值由原节点记录
            //达到了'删除'原节点并保持中序遍历顺序不变的效果
            now->left = next->left;
        }
        delete next;//删除多余的节点
    }
}

void AVL_Delete(AVL &tree, int data) {
    if (tree == nullptr) {
    }
    else if (tree->data == data) {
        Delete(tree);
    }
    else if (data < tree->data) {
        AVL_Delete(tree->left, data);
    }
    else if (data > tree->data) {
        AVL_Delete(tree->right, data);
    }
    if (tree) {
        Rotate(tree, data);
    }
}

bool AVL_Search(AVL tree, int data, AVL &elem) {
    if (tree == nullptr) {
        elem = nullptr;
        return false;
    }
    else if (tree->data == data) {
        elem = tree;
        return true;
    }
    else if (data < tree->data) {
        return AVL_Search(tree->left, data, elem);
    }
    else {
        return AVL_Search(tree->right, data, elem);
    }
}

void print(AVL tree) {
    if (tree) {
        print(tree->left);
        cout << tree->data << ' ';
        print(tree->right);
    }
}

void pre(AVL tree) {
    if (tree) {
        cout << tree->data << ' ';
        pre(tree->left);
        pre(tree->right);
    }
}

int main() {
    AVL tree = nullptr;
    AVL_Insert(tree, 10);
    AVL_Insert(tree, 20);
    AVL_Insert(tree, 30);
    AVL_Insert(tree, 40);
    AVL_Insert(tree, 70);
    AVL_Insert(tree, 55);
    AVL_Insert(tree, 50);
    AVL_Insert(tree, 25);
    cout << "先序遍历: ";
    pre(tree);
    cout << endl;
    cout << "中序遍历: ";
    print(tree);
    cout << endl;
    cout << endl;
    AVL_Delete(tree, 30);
    cout << "先序遍历: ";
    pre(tree);
    cout << endl;
    cout << "中序遍历: ";
    print(tree);
    cout << endl;
    cout << endl;
    AVL_Delete(tree, 25);
    cout << "先序遍历: ";
    pre(tree);
    cout << endl;
    cout << "中序遍历: ";
    print(tree);
    cout << endl;
    cout << endl;
    AVL_Insert(tree, 25);
    cout << "先序遍历: ";
    pre(tree);
    cout << endl;
    cout << "中序遍历: ";
    print(tree);
    cout << endl;
    cout << endl;
    AVL_Insert(tree, 30);
    cout << "先序遍历: ";
    pre(tree);
    cout << endl;
    cout << "中序遍历: ";
    print(tree);
    cout << endl;
    return 0;
}