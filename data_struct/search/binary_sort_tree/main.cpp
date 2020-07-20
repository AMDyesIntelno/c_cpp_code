/*二叉排序树*/
#include<iostream>

using namespace std;
typedef struct Binary_Sort_Tree {
    int data;
    struct Binary_Sort_Tree *left = nullptr;
    struct Binary_Sort_Tree *right = nullptr;
} *BST;

void BST_Insert(BST &tree, int data) {
    if (tree == nullptr) {
        tree = new Binary_Sort_Tree;
        tree->data = data;
    }
    else if (tree->data == data) {
        return;
    }
    if (data < tree->data) {
        BST_Insert(tree->left, data);
    }
    else {
        BST_Insert(tree->right, data);
    }
}

bool BST_Search(BST tree, int data, BST &elem) {
    if (tree == nullptr) {
        elem = nullptr;
        return false;
    }
    else if (tree->data == data) {
        elem = tree;
        return true;
    }
    else if (data < tree->data) {
        return BST_Search(tree->left, data, elem);
    }
    else {
        return BST_Search(tree->right, data, elem);
    }
}

int find_max(BST tree) {
    if (tree) {
        if (tree->right) {
            return find_max(tree->right);
        }
        return tree->data;
    }
    else {
        return INT32_MIN;
    }
}

int find_min(BST tree) {
    if (tree) {
        if (tree->left) {
            return find_min(tree->left);
        }
        return tree->data;
    }
    else {
        return INT32_MIN;
    }
}

void Delete(BST &tree) {
    BST now = nullptr, next = nullptr;
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

void BST_Delete(BST &tree, int data) {
    if (tree == nullptr) {
    }
    else if (tree->data == data) {
        Delete(tree);
    }
    else if (data < tree->data) {
        BST_Delete(tree->left, data);
    }
    else {
        BST_Delete(tree->right, data);
    }
}

void BST_Destroy(BST &tree) {
    if (tree) {
        BST_Destroy(tree->left);
        BST_Destroy(tree->right);
        delete tree;
    }
}

void print(BST tree) {
    if (tree) {
        print(tree->left);
        cout << tree->data << " ";
        print(tree->right);
    }
}

int main() {
    BST tree = nullptr;
    int n, temp;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> temp;
        BST_Insert(tree, temp);
    }
    print(tree);
    cout << endl;
    cout << "max: " << find_max(tree) << endl;
    cout << "min: " << find_min(tree) << endl;
    BST_Delete(tree, 5);
    print(tree);
    cout << endl;
    BST_Insert(tree, 5);
    print(tree);
    cout << endl;
    BST_Destroy(tree);
    tree = nullptr;
    return 0;
}