// 删除值相同的元素,保证时间复杂度O(n),空间复杂度为O(1)->双指针法
// 坑点:列表长度也要随之更新
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
void Delete_same_value(SqList &L,Elemtype e) {
    int j = 0; // 引入一个常量(双指针)表示当前紧凑顺序表的尾部
    for(int i=0;i<L.length;i++) {
        if (L.data[i]!=e) {
            L.data[j] = L.data[i]; //一直保证紧凑
            j++;
        }
    }
    L.length = j; //!!保证干净(扣大分)
}
int main(){}
