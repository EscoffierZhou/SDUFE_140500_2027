#include <iostream>
#include <cstdio>
#define MAXLEN 255

using namespace std;

// ==========================================
// 1. 串的定长顺序存储表示 (Sequential Storage)
// ==========================================
// 栈分配:编译器自动分配释放,用于存储局部变量
typedef struct {
    // char ch[MAXLEN + 1];     // 则是[0]存储串的长度(KMP)
    char ch[MAXLEN];
    int length;
}SString;
void InitSString(SString &S) {
    S.length=0;
}

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

// ==========================================
// 3. 串的块链存储表示 (Block Chain Representation)
// ==========================================
#define CHUNKSIZE 80            // 块大小
struct Chunk {
    char ch[CHUNKSIZE];
    Chunk *next;
    // struct Chunk *next;      // 老C语言方言
};
struct LString {
    Chunk *head, *tail;         // 串的头和尾指针，带尾指针方便拼接操作
    int length;                 // 串的当前长度
};
bool InitLString(LString &S) {  // 使用头结点统一后序操作
    S.head = (Chunk *)malloc(sizeof(Chunk));
    if (!S.head) return false;
    S.head->next =NULL;
    S.tail = S.head;
    S.length = 0;
    return true;
}
/* C-Style(注意使用的是*和malloc,C++一般是&和neew)
bool InitLString_C(LString *S) {
    S->head = (Chunk *)malloc(sizeof(Chunk));
    if (!S->head) return false;
    ...}
*/
// ==========================================
int main() {
    // 1. 测试定长顺序串
    SString s1;
    InitSString(s1);
    cout << "[SString] 初始化完成，当前长度: " << s1.length << std::endl;

    // 2. 测试堆分配串
    HString s2;
    InitHString(s2);
    cout << "[HString] 初始化完成，指针状态: " << (s2.ch == NULL ? "NULL" : "非空") << std::endl;

    // 3. 测试块链串
    LString s3;
    InitLString(s3);
    cout << "[LString] 初始化完成，头尾指针是否重合: " << (s3.head == s3.tail ? "是" : "否") << std::endl;
    // 极其重要的习惯:分配了堆内存的块链，程序结束前必须手动释放，防止内存泄漏
    delete s3.head;

    return 0;
}