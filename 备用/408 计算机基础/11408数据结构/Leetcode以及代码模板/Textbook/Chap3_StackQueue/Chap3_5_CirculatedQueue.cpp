#include<iostream>
#define MaxSize 50
using namespace std;

typedef int ElemType;
typedef struct{
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}
/*
// 当前进考虑白给一位当作头节点的情况:
bool QueueEmpty_size(int size) {return size==0;}
bool QueueEmpty_flag(SqQueue Q,bool flag) {return flag;}
*/
// 加上const避免全量粘贴
bool QueueEmpty(const SqQueue Q) {
    return Q.front == Q.rear;
}
bool QueueFull(const SqQueue Q) {
    return (Q.rear + 1) % MaxSize == Q.front;
}
int QueueSize(const SqQueue Q) {
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}
bool EnQueue(SqQueue &Q,ElemType x) {   // 默认入队少一个元素做哨兵节点
    if ((Q.rear + 1)%MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize; // 不能单纯增加1否则假溢出
    return true;
}
bool DeQueue(SqQueue &Q,ElemType &x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}
int main() {
    SqQueue Q1;
    InitQueue(Q1);
    EnQueue(Q1,1);
    EnQueue(Q1,1);
    EnQueue(Q1,1);
    cout << QueueSize(Q1) << endl;
}
