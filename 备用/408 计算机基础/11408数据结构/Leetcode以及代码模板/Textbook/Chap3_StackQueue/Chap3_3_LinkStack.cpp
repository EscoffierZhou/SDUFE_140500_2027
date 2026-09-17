#include<iostream>
using namespace std;
typedef int ElemType;
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
} LinkNode, *LiStack;   // 链式存储结构必备*LiStack;
// 和链表不同的是:无头结点所以只需要初始化一个指针
// 同时Push是FILO,所以是反着插就好

bool InitStack(LiStack &S) {
    S = NULL; // 栈顶指针直接置空
    return true;
}
bool Push(LiStack &S, ElemType x) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    if (!p) return false; // 内存分配失败（注意 !p 才是分配失败）
    p->data = x;
    p->next = S; // 新节点的 next 指向当前的栈顶节点
    S = p;       // 栈顶指针 S 上移，指向这个新节点
    return true;
}
bool Pop(LiStack &S, ElemType &x) {
    if (S == NULL) return false; // 栈空，无法出栈
    LinkNode *p = S;
    x = p->data;     // 取出数据
    S = S->next;     // 栈顶指针 S 下移，指向下一个节点
    free(p);         // 释放原栈顶节点的内存（防止内存泄漏）
    return true;
}
// 4. 读取栈顶 (O(1))
bool GetTop(const LiStack &S, ElemType &x) { // 注意这里加了 &
    if (S == NULL) return false;
    x = S->data;
    return true;
}
int main() {
    LiStack S1;
    InitStack(S1);
    Push(S1, 1);
    Push(S1, 2);
    Push(S1, 3);
    ElemType x;
    Pop(S1, x);
    GetTop(S1,x);
    Pop(S1, x);
}
