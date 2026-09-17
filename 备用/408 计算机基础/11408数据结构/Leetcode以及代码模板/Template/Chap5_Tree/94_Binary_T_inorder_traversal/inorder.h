#ifndef INORDER_94_H
#define INORDER_94_H

#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    // 构造函数:首先它是函数,其次函数名相同,直接调用本身
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// C++ 版本(题目里面其实有)
// 注意形参里面的struct可写可不写,不能写auto(C++17:形参里面不能用auto)
inline void inorder_cpp(TreeNode* root, std::vector<int>& res) {
    // vector<int>:自动扩容,自动记录 size
    // & res:引用传参,所有递归共享同一个 res
    if (!root) return;
    inorder_cpp(root->left, res);       // 左
    res.push_back(root->val);           // 中
    inorder_cpp(root->right, res);      // 右
}

// C 版本(题目里面其实有,C 语言没有可自动增长的容器，也没有引用传参)
// 注意形参里面的struct必写,因为C语言要求首次必须声明类型->除非typedef
inline void inorder_c(struct TreeNode* root, int* res, int* resSize) {
    if (!root) return;
    inorder_c(root->left, res, resSize); // 左
    // res[(*resSize)++] = root->val; // 模拟动态数组+size
    res[*resSize] = root->val;          // 中 把值放到“当前尾部”
    *resSize = *resSize + 1; // 尾部指针后移
    inorder_c(root->right, res, resSize); // 右
}

#endif
