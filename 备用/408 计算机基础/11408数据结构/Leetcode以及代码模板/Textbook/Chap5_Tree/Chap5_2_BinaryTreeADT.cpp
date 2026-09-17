#include<iostream>
#include<cstdio>
using namespace std;
// 408:要求typdef的C风格代码,虽然现代可以用unique_ptr和vector
// 顺序存储:需要区分标记位和实际的数据->使用bool
//    效果:对于(满)完全二叉树是完美的,但是对于普通二叉树是致命的
#define MAX_SIZE 100
typdef int ElemType;
typedef struct {
    Elemtype data[MAX_SIZE + 1];
    bool isEmpty[MAX_SIZE + 1];
}SqBiTree;
void Init_SqBiTree(SqBiTree &T) {       // 全部置空
    for(int i=0;i<= MAX_SIZE;i++){}
    T.isEmpty[i] = true;
}

// 链式存储:包含数据域和左右双指针
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;
void InitEmptyTree(BiTree &root) { // 初始化空树
    root = NULL;
}
bool InitRootNode(BiTree &root,ElemType val) {
    root = (BiTree)malloc(sizeof(BiTNode));
    if(root==NULL) { // 内存分配失败
        return false;
    }
    root->data = val;
    root->lchild = root->rchild = NULL;
    return true;
}


// 三叉链表:等价于双向链表
typedef struct TriNode {
    ElemType data;
    struct TriNode *lchild, *rchild;
    struct TriNode *parent;
}TriNode,*TriTree;

// 孩子兄弟表示法:
typedef  struct CSNode {
    ElemType data;
    struct CSNode *firstChild;
    struct CSNode *nextsiblling;
};
