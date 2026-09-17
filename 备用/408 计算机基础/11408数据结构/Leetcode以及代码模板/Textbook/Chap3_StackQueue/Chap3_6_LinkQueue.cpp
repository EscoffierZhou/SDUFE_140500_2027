#include<iostream>
#define MaxSize 50
using namespace std;

typedef int ElemType;
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
// 更简化的写法:同时声明了一个带有头尾指针的结点
typedef struct{
    LinkNode *front,*rear;
}LinkQueue;
// 注意:以下运算是带头节点的尾插法(front始终指向头节点,rear指向尾结点)

void InitQueue(LinkQueue &Q){
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
    // Q.front=Q.rear=new LinkNode;
    Q.front->next=NULL;
    // Q.rear=Q.front; 王道上面没有加上
}
bool QueueEmpty(const LinkQueue &Q){
    // return Q.front->next==NULL; 应该也可以
    return Q.front==Q.rear;
}
int QueueLength(LinkQueue &Q){ // 带头节点
    int len=0;
    LinkNode *p = Q.front->next;
    while (p){
        len++;
        p=p->next;
    }
    return len;
}

bool EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
    if (!s) return false;
    s->data=x;
    s->next = Q.rear->next;
    Q.rear->next=s;
    Q.rear = s;
    return true;
}

bool DeQueue(LinkQueue &Q,ElemType &x){
    if (Q.front == Q.rear)
        return false;
    LinkNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)     // 关键:如果删最后一个元素,rear可能野指针
        Q.rear = Q.front;
    free(p);
    return true;
}


int main() {
    LinkQueue Q1;
    InitQueue(Q1);
    EnQueue(Q1,2);
    EnQueue(Q1,10);
    cout << QueueLength(Q1)<<endl;
}