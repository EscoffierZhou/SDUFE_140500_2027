// (1)从顺序表中删除最小值的元素,由函数返回元素的值
// (2)空出的位置由最后一个元素填充
// (3)顺序表为空则显示错误信息
// !!!最后一个元素是[L.length-1]
// 202318140413
#include<iostream>
using namespace std;
#define MAXSIZE 100
#define OVERFLOW 0
#define OK 1
#define ERROR -1
typedef int datatype;
typedef int Status;
typedef struct {
    datatype* data;
    int length;
} SqList;
// 定义了匿名struct类型,这个类型叫做Sqlist

// struct List {
    // datatype* data;
    // int length;
// } SqList;
// 定义了struct类型,叫做List,并且声明了一个变量SqList

bool Delete_minimum(SqList &L, datatype &value) {
    if (L.length == 0)return false;
    datatype min = L.data[0];
    int index = 0;
    // (1) 找最小值及其下标
    for (int i = 1; i < L.length; i++) {
        if (L.data[i] < min) {
            min = L.data[i];
            index = i;
        }
    }
    value = min;
    // (2) 用最后一个元素填补
    L.data[index] = L.data[L.length-1];
    L.length--;
    return true;
}
