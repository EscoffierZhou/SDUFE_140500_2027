#include<iostream>
#define MaxSize 50
using namespace std;

typedef int ElemType;
typedef struct{
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

// 单队列已经在物理规律里面已经"死了"
bool InitQueue(SqQueue &Q) {
    Q.front = 0;
    Q.rear = 0;
    return true;
}
bool QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}
bool EnQueue(SqQueue &Q,ElemType x) {
    // 王道说可以假溢出,偷个懒,但是Gemini说不行
    if (Q.rear==MaxSize)return false;
    Q.data[Q.rear++] = x;
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x) {
    x = Q.data[Q.front++];
    return true;
}

bool getFirst(SqQueue &Q,ElemType &x) {
    x = Q.data[Q.front];
    return true;
}
