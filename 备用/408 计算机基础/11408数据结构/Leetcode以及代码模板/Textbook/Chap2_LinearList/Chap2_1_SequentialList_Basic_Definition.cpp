#include<iostream>
#include <cstdio>
#define MAXSIZE 50
#define InitSize 100
typedef double ElemType;
using namespace std;

// (1)分配存储(静态)
typedef struct {
    ElemType data[MAXSIZE];
    int Length;
}SqList_ignore;
// (2)分配存储(动态)
typedef struct {
    ElemType *data;
    int Maxsize,Length;
}SqList;

//(3)顺序表的初始化(静态)
void InitList_static(SqList &L) {
    // 声明的时候内存已经分配了
    L.Length = 0;
}
//(4)顺序表的初始化(动态)
void InitList_(SqList &L) {
    L.data = (ElemType*)malloc(InitSize *sizeof(ElemType));
    L.Maxsize = MAXSIZE;
    L.Length = 0;
}

//(5)插入操作:在第i位置插入新元素e
bool ListInsert(SqList &L, int i, ElemType e) {
    if (i<1||i>L.Length+1)
        return false;
    if (L.Length>=L.Maxsize)
        return false;
    for (int j=L.Length;j>=i;j--)
        L.data[j] = L.data[j-1];
    L.data[i-1] = e;
    L.Length++;
    return true;
}

//(6)删除操作:删除顺序表L第i个元素,使用引用参数返回其值
bool ListDelete(SqList &L,int i,ElemType &e) {
    if (i<1||i>L.Length)
        return false;
    e = L.data[i-1];
    for (int j=i;j<L.Length;j++)
        L.data[j-1] = L.data[j];
    L.Length--;
    return true;
}

//(7)按值查找:
int LocateElem(SqList L,ElemType e) {
    int i;
    for (i=0;i<L.Length;i++) {
        if (L.data[i]==e)
            return i+1;
    }
    return 0;
}

int main() {
    SqList L;
    L.data = new ElemType[InitSize];
    L.data = (ElemType*)malloc(InitSize*sizeof(ElemType));

}