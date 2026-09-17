#include<iostream>
#include <stack>
using namespace std;
#define MaxSize 50
typedef int ElemType;
// 入栈:先向上挪动一个空位,然后放置数据
// 出栈:先拿走栈顶元素,然后指针回退
// top=-1 的时候指向的是栈顶元素;          入栈:需要先移动指针然后放置  出栈:直接移动栈顶元素
// top=0  的时候指向的是栈顶元素的下一个元素  入栈:直接放置,然后移动指针  出栈:需要移动指针到栈顶元素,然后再释放
// 共享栈的不同:不能声明两个SA和SB否则是两个分开的栈,除此之外额外新增stackNum决定操作的栈


// 1. 真正的共享栈 ADT 定义
typedef struct {
    ElemType data[MaxSize]; // 唯一的一个共享数组
    int top0;
    int top1;
} ShStack;

// 2. 初始化
void InitStack(ShStack &S) {
    S.top0 = -1;       // 0号栈初始指向下边界之外
    S.top1 = MaxSize;  // 1号栈初始指向上边界之外
}

// 3. 入栈 (必须指明入哪个栈)
// stackNum: 0代表压入0号栈，1代表压入1号栈
bool Push(ShStack &S, int stackNum, ElemType x) {
    // 唯一判断栈满的条件：两指针相邻
    // 反向思维则是:S.top1-S.top0=1
    if (S.top0 + 1 == S.top1) {
        return false;
    }
    if (stackNum == 0) {
        S.data[++S.top0] = x; // 0号栈先上移指针，再赋值
    } else if (stackNum == 1) {
        S.data[--S.top1] = x; // 1号栈先下移指针，再赋值
    } else {
        return false; // 非法的栈号
    }
    return true;
}

// 4. 出栈 (必须指明出哪个栈)
bool Pop(ShStack &S, int stackNum, ElemType &x) {
    if (stackNum == 0) {
        if (S.top0 == -1) return false; // 0号栈空
        x = S.data[S.top0--];
    } else if (stackNum == 1) {
        if (S.top1 == MaxSize) return false; // 1号栈空
        x = S.data[S.top1++];
    } else {
        return false;
    }
    return true;
}
bool GetTop(const ShStack &S, int stackNum, ElemType &x) {
    // 边界条件是没有初始化
    if (stackNum == 0) {
        if (S.top0 == -1) {
            return false; // 0号栈为空，拒绝读取
        }
        x = S.data[S.top0];
    } else if (stackNum == 1) {
        if (S.top1 == MaxSize) {
            return false; // 1号栈为空，拒绝读取
        }
        x = S.data[S.top1];
    } else {
        return false; // 非法的栈号
    }
    return true; // 读取成功
}

int main() {
    ShStack S;
    InitStack(S);
    // 养成测试边界条件的好习惯
    ElemType test_empty;
    if (!GetTop(S, 0, test_empty)) {
        cout << "Stack 0 is empty, GetTop failed safely." << endl;
    }
    Push(S, 0, 1);
    Push(S, 1, 10);
    ElemType a, b;
    if (GetTop(S, 0, a) && GetTop(S, 1, b)) {
        cout << a << " " << b << endl;
    }
    return 0;
}