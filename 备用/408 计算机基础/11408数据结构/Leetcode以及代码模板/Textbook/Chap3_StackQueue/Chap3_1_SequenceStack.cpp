#include<iostream>
using namespace std;
#define MaxSize 50
typedef int ElemType;
// 入栈:先向上挪动一个空位,然后放置数据
// 出栈:先拿走栈顶元素,然后指针回退
// top=-1 的时候指向的是栈顶元素;          入栈:需要先移动指针然后放置  出栈:直接移动栈顶元素
// top=0  的时候指向的是栈顶元素的下一个元素  入栈:直接放置,然后移动指针  出栈:需要移动指针到栈顶元素,然后再释放

// ADT定义:Stack和Queue不同
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S){
    S.top=-1;
}
bool StackEmpty(SqStack S){
    return S.top==-1; //这样也直接返回True-False
}
bool Push(SqStack &S,ElemType x){
    if(S.top==MaxSize-1)
        return false;
    S.data[++S.top]=x;
    // 如果初始化为0,则S.data[S.top++]=x
    return true;
}
bool Pop(SqStack &S,ElemType &x){
    if(S.top==-1)
        return false;
    x = S.data[S.top--];
    // 如果初始化为0,则x = S.data[--S.top]
    return true;
}
bool GetTop(SqStack S,ElemType &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top];
    return true;
}
int main() {
    SqStack S;
    InitStack(S);
    Push(S, 10);
    Push(S, 20);

    ElemType val;
    if (Pop(S, val)) {
        cout << "Popped: " << val << endl;
    }
    return 0;
}