#include <iostream>
#include <vector>
#include <cstdlib>
#include "inorder.h"
using namespace std;
class Solution_Cpp_2 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root, res);
        return res;
    }
    void preorder(TreeNode* root, vector<int>& res) {
        if (!root) {
            return;
        }
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }
};

class Solution_C_2{
public:
    // 注意C语言要求:(1)type(2)函数位置,放个原型(3)类内都是完整声明不需要模板
    int* preorderTraversal(struct TreeNode* root, int* returnSize) {
        int* res = (int*)malloc(sizeof(int) * 501);
        *returnSize = 0;
        preorder(root, res, returnSize);
        return res;
    }
    void preorder(struct TreeNode* root, int* res, int* resSize) {
        if (!root) {
            return;
        }
        res[(*resSize)++] = root->val;
        preorder(root->left, res, resSize);
        preorder(root->right, res, resSize);
    }
    // 删树只能最后删根,不然UB
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
    cout << "Binary T(preorder):(root-left-right)"<<endl<<
         """       1\n"
         "      / \\\n"
         "     2   3\n"
         "    /    /\n"
         "   4    5""" << endl;
    // C++
    Solution_Cpp_2 cpp_sol;
    vector<int> cpp_res = cpp_sol.preorderTraversal(root);
    cout << "C++ Result: ";
    for (int val : cpp_res) cout << val << " ";
    cout << endl;

    // C
    Solution_C_2 c_sol;
    int returnSize = 0;
    int* c_res = c_sol.preorderTraversal(root, &returnSize);
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