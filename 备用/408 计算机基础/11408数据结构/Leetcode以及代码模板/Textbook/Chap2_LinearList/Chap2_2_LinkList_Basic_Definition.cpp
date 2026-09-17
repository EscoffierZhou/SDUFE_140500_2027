#include <iostream>
#include <cstdlib>
// (1)新建结点后必接内存判断:    LNode *s = (LNode *)malloc(sizeof(LNode)); -> if (s == NULL) return false;
// (2)结点指针遍历后必须判边界:   LNode *p = L;while(p!=NULL&&j<i-1){...};   -> if (p == NULL) return false;

using namespace std;
typedef int ElemType; // 假设数据类型为 int

typedef struct LNode {
    ElemType data;      // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;
// 等价于
// (1)定义结构体      :
// (2)重命名结构体    typedef struct LNode LNode;
// (3)重命名结构体指针 typedef struct LNode *LinkList;  将 struct LNode * (指向该结构体的指针) 重命名为 "LinkList"

// LinkList L	类型:指针	    "我是一个单链表"	强调这是链表的头指针，代表整个链表。
// LNode *p	    类型:指针	    "我是一个结点指针"	强调这是指向某个具体结点的游标，用于扫描、遍历。
// LinkList 等价于 LNode*
// 使用 LinkList L 强调这是链表
// 使用 LNode *p 强调这是个结点指针
// 主要用法:bool InitList(LNode *&L);"结点不直观"  ->  bool InitList(LinkList &L);"直接链表直观"

bool InitList(LinkList &L) {
    L = (LNode *)malloc(sizeof(LNode)); // 分配头结点
    if (L == NULL) return false;            // 边界判断:内存分配失败
    L->next = NULL;
    return true;
}

int Length(LinkList L) {
    int len = 0;
    LNode *p = L;  // 头指针开始:因为首元结点可能不存在
    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

LNode* GetElem(LinkList L, int i) {
    if (i < 0) return NULL;
    LNode *p = L;  // 头指针开始:因为头节点算作第0个结点
    int j = 0;
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    return p;      // 如果i超出表长,p直接返回NULL也是正确的
}

LNode* LocateElem(LinkList L, ElemType e) {
    LNode *p = L->next; // 从首元结点开始找:头结点没数据
    while (p != NULL && p->data != e) {
        p = p->next;
    }
    return p;
}

bool ListInsert_back(LinkList &L, int i, ElemType e) {
    // 1. 找到第 i-1 个结点 (前驱)
    LNode *p = L;
    int j = 0;
    while (p != NULL && j < i - 1) {
        p = p->next; j++;
    }
    if (p == NULL) return false;
    // 2. 只有标准的后插操作(O(1))
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s == NULL) return false;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListInsert_forward(LinkList &L, int i, ElemType e) { // p已知就:LNode *p
    // 1.找到第i个结点(可选)
    // LNode *p = L;
    // int j = 0;
    // while (p != NULL && j < i) {
    //    p = p->next; j++;
    //}
    if (p == NULL) return false;
    // 2.只有标准的后插操作(O(1))
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s == NULL) return false;
    s->next = p->next;
    p->next = s;
    Elemtype temp = p->data; // 旧数据
    p->data = e;    // 新数据在前面
    s->data = temp; // 旧数据在后面
    return true;
}