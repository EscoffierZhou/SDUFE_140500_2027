#include <iostream>
#include <cstdio>
#define MAXLEN 255
// 时间复杂度O(nm)
using namespace std;
typedef struct {
    char ch[MAXLEN + 1]; // 由AddChar和算法决定
    int length;
}SString;
void InitSString(SString &S) {
    S.length=0;
}
bool AddChar(SString &S,char c) {
    if (S.length<MAXLEN) {
        S.ch[++S.length]=c; // ch[0]闲置,所以是从ch[1]开始存储
        return true;
    }
    return false;
}
int Index(SString S,SString T) {
    int i=1,j=1;
    while (i<=S.length && j<=T.length) {
        if (S.ch[i]==T.ch[j]) {
            i++;j++;
        }
        else {
            i=(i-j+1)+1;   // i-j+1回到的是当前的位置
            j=1;           // 长串指针i向后移动一位,j初始化为1
        }
    }
    // 进一步判断条件
    if (j > T.length) {
        return i - T.length;    // 这时候i已经在匹配串的最后一位了
    } else {
        return 0; // 0 在这里表示匹配失败，因为我们合法下标从 1 开始
    }
}

int main() {
    SString S,T;
    InitSString(S);
    InitSString(T);
    string str1 = "ababcabcacbab";
    string str2 = "abcac";
    for (int i=0;i<str1.length();i++) {
        AddChar(S,str1[i]);
    }
    for (int i=0;i<str2.length();i++) {
        AddChar(T,str2[i]);
    }
    int pos = Index(S, T);
    if (pos > 0) {
        std::cout << "在下标 " << pos << " 处找到匹配！" << std::endl;
    } else {
        std::cout << "未找到匹配！" << std::endl;
    }
    return 0;
}
