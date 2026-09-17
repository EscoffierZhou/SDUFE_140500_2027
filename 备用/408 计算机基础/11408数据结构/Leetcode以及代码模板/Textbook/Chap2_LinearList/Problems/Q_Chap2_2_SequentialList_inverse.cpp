// 将顺序表逆置,保证空间复杂度为O(1)
#include<iostream>
using namespace std;
#define MAXSIZE 100
#define OVERFLOW 0
#define OK 1
#define ERROR -1
typedef int Elemtype;
typedef int Status;
typedef struct {
    Elemtype* data;
    int length;
} SqList;

// 注意等价于:struct List{};List SqList;  (定义了一个全局变量)
void SequentialList_inverse(List &L) {
    int a=0;
    for (int i = 0;i<L.length/2;i++) {
        a = L.data[L.length-1-i];
        L.data[L.length-1-i] = L.data[i];
        L.data[i] = a;
    }
}

