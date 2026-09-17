// 中序遍历:左子树-根节点-右子树的方式进行遍历
// 整体思路:
// 1.定义一个vector用于存储结果(C++:STL/C:链式存储malloc)
// 2a.进行中序遍历(Cpp)
// a.判空,返回空vector
// b.递归调用inorder(root->left),push_back,inorder(root->right)
// c.返回结果
// 2b.进行中序遍历(Cpp)
// a.判空,返回空vector
// b.递归调用inorder(root->left),push_back,inorder(root->right)
// c.返回结果

#include <iostream>
#include <vector>
#include <cstdlib>
#include "inorder.h"
using namespace std;
class Solution_Cpp {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
    void inorder(TreeNode* root, vector<int>& res) {
        if (!root) {
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
};

class Solution_C{
public:
    // 注意C语言要求:(1)type(2)函数位置,放个原型
    int* inorderTraversal(struct TreeNode* root, int* returnSize) {
        int* res = (int*)malloc(sizeof(int) * 501);
        *returnSize = 0;
        inorder(root, res, returnSize);
        return res;
    }
    void inorder(struct TreeNode* root, int* res, int* resSize) {
        if (!root) {
            return;
        }
        inorder(root->left, res, resSize);
        res[(*resSize)++] = root->val;
        inorder(root->right, res, resSize);
    }
    void destroyTree(TreeNode* root) {
        if (root == nullptr) return;
        destroyTree(root->left);  // 先杀左子树
        destroyTree(root->right); // 再杀右子树
        delete root;              // 最后杀根节点（后序遍历的应用）
    }
};

int main() {
    // TreeNode* root   = new TreeNode(1);
    auto root        = new TreeNode(1);
    root->left       = new TreeNode(2);
    root->right      = new TreeNode(3);
    root->right->left= new TreeNode(5);
    root->left->left = new TreeNode(4);
    cout << "Binary T(inorder):(left-root-right)"<<endl<<
         """       1\n"
         "      / \\\n"
         "     2   3\n"
         "    /    /\n"
         "   4    5""" << endl;

    // C++
    Solution_Cpp cpp_sol;
    vector<int> cpp_res = cpp_sol.inorderTraversal(root);
    cout << "C++ Result: ";
    for (int val : cpp_res) cout << val << " ";
    cout << endl;

    // C
    Solution_C c_sol;
    int returnSize = 0;
    int* c_res = c_sol.inorderTraversal(root, &returnSize);
    cout << "C Result:   ";
    for (int i = 0; i < returnSize; i++) {
        cout << c_res[i] << " ";
    }
    cout << endl;

    // --- 4. 释放内存 (良好的编程习惯) ---
    free(c_res);
    c_sol.destroyTree(root);
    return 0;
}

//       1
//      / \
//     2   3
//    /
//   4