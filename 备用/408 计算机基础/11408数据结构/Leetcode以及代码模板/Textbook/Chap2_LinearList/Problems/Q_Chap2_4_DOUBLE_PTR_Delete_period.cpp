// 删除值s和t之间的元素(s<t),s和t的关系以及顺序表为空则返回错误
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
bool Delete_between_st(SqList &L,Elemtype s,Elemtype t) {
    if (L.length == 0)return false;
    if (s>=t)return false;
    int j=0;
    for(int i=0;i<L.length;i++) {
        if (L.data[i]<=s||L.data[i]>=t) {
            L.data[j] = L.data[i]; //一直保证紧凑
            j++;
        }
    }
    L.length = j; //!!保证干净
    return true;
}
int main(){}
