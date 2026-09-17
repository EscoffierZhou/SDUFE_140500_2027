// 必死前提(1):节点值互不相同,如果存在相同值也可能有不同树
// 必死前提(2):所有的遍历序列都要来自同一个树,只给两个序列可能写不出来
// 必死前提(3):左右子树的规模是否确定
//==============================================================
// 已知:前序(pre) + 中序(in) = 确定的二叉树(根左右+左根右)->确定左&根->根确定(二维表格)
// 已知:后序(post)+ 中序(in) = 确定的二叉树(左右根+左根右)->确定右&根->根确定(二维表格)
// 已知:前序(pre) + 后序(post) = 无法确定二叉树(根左右+左右根)->无法确定二维表格
// !!!特殊:前序(pre) + 后序(post) + 满二叉树:可以确定唯一二叉树
// 已知:一种遍历顺序->无法确定二维表格
//==============================================================
//“定树必有中，前后不能凑；前中、后中行，前后要满树。”
// 构树O(n)一定要用哈希表
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include "inorder.h"
using namespace std;

TreeNode* buildTreePreIn(const vector<int>& preorder,int preL,int preR,
                         const vector<int>& inorder, int inL, int inR,
                         unordered_map<int, int>& pos
                        ){
    // (1)左右子树规模不同,直接死
    if (preL > preR) return nullptr;
    // (2)
    int rootVal = preorder[preL];
    TreeNode* root = new TreeNode(rootVal);
    int k = pos[rootVal];              // 根在中序的位置
    int leftSize = k - inL;

    root->left = buildTreePreIn(
            preorder, preL + 1, preL + leftSize,
            inorder,  inL, k - 1,
            pos
    );
    root->right = buildTreePreIn(
            preorder, preL + leftSize + 1, preR,
            inorder,  k + 1, inR,
            pos
    );
    return root;
}
TreeNode* buildTreePostIn(const vector<int>& postorder, int postL, int postR,
                          const vector<int>& inorder,   int inL,   int inR,
                          unordered_map<int, int>& pos
                         ){
    // (1)左右子树规模不同,直接死
    if (postL > postR) return nullptr;
    int rootVal = postorder[postR];
    TreeNode* root = new TreeNode(rootVal);
    int k = pos[rootVal];
    int leftSize = k - inL;
    root->left = buildTreePostIn(
            postorder, postL, postL + leftSize - 1,
            inorder,   inL,   k - 1,
            pos
    );
    root->right = buildTreePostIn(
            postorder, postL + leftSize, postR - 1,
            inorder,   k + 1, inR,
            pos
    );
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> pos;
    for (int i = 0; i < inorder.size(); ++i)
        pos[inorder[i]] = i;
    return buildTreePreIn(
            preorder, 0, preorder.size() - 1,
            inorder,  0, inorder.size() - 1,
            pos
    );
}

TreeNode* buildTreeFromPost(vector<int>& postorder, vector<int>& inorder) {
    unordered_map<int, int> pos;
    for (int i = 0; i < inorder.size(); ++i)
        pos[inorder[i]] = i;
    return buildTreePostIn(
            postorder, 0, postorder.size() - 1,
            inorder,  0, inorder.size() - 1,
            pos
    );
}

int main() {
    vector<int> preorder = {1, 2, 4, 3, 5};
    vector<int> inorder = {4, 2, 1, 5, 3};
    vector<int> postorder = {4, 2, 5, 3, 1};

    cout << "二叉树(中序):(左-根-右)"<<endl<<
         "       1\n"
         "      / \\\n"
         "     2   3\n"
         "    /    /\n"
         "   4    5" << endl;

    cout << "\n通过前序和中序遍历构建树..." << endl;
    TreeNode* root_from_pre = buildTree(preorder, inorder);
    vector<int> result_inorder_pre;
    inorder_cpp(root_from_pre, result_inorder_pre);
    cout << "构建树的中序遍历: ";
    for (int val : result_inorder_pre) {
        cout << val << " ";
    }
    cout << endl;

    cout << "\n通过后序和中序遍历构建树..." << endl;
    TreeNode* root_from_post = buildTreeFromPost(postorder, inorder);
    vector<int> result_inorder_post;
    inorder_cpp(root_from_post, result_inorder_post);
    cout << "构建树的中序遍历: ";
    for (int val : result_inorder_post) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
