#include <iostream>
#include <cstdio>
using namespace std;
// ==========================================
// 2. 串的堆分配存储表示 (Heap Allocation)
// ==========================================
// 堆分配:程序员动态申请的内存池,手动new/delete;malloc/free
struct HString {
    char *ch;                   // 如果是非空串,则按指定长度分配存储区,否则ch为NULL
    int length;                 // 串的实际长度
};
void InitHString(HString &S) {
    S.ch=NULL;                  // 初始未分配任何堆内存
    S.length=0;
}
bool AddChar(HString &S,const chat *chars) {
    // 如果被赋值前S已经有值了,需要释放
    if (S.ch!=NULL) {
        delete[] S.ch;
        S.ch = NULL;
    }
    int len = strlen(chars);
    // (1)传入空串
    if (len==0){
        S.length = 0;
        return true;
    }
    // (2)新建堆内存
    S.ch = new char[len];
    if (S.ch==NULL) { // 内存分配失败
        return false;
    }
    // (3)加入新的内存中
    for (int i=0; i<len; i++) {
        S.ch[i] = chars[i];
    }
    S.length = len;
    return true;
}
void DestroyHString(HString &S) {
    if (S.ch!=NULL) {
        delete[] S.ch;
        S.ch = NULL;
    }
    S.length = 0;
}
int main() {
    HString S;
    InitHString(S);
    if (StrAssign(S, "Hello UESTC")) {
        std::cout << "首次赋值成功，当前长度: " << S.length << std::endl;
    }
    if (StrAssign(S, "AI")) {
        std::cout << "覆盖赋值成功，当前长度: " << S.length << std::endl;
    }
    DestroyHString(S);
    return 0;
}