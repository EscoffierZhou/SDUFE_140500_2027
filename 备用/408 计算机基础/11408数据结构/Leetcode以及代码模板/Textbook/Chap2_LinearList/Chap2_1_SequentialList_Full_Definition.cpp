//202318140413
#include<iostream>
using namespace std;
typedef int Elemtype;
typedef int Status;
#define MAXSIZE 100
#define OVERFLOW 0
#define OK 1

struct List {
    Elemtype* elem;
    int length;
};

// 初始化线性表
Status InitList(List& L) {
    L.elem = new Elemtype[MAXSIZE];
    if (!L.elem) return OVERFLOW;
    L.length = 0;
    return OK;
}

// 销毁线性表
Status DestroyList(List& L) {
    delete[] L.elem;
    L.elem = nullptr;
    L.length = 0;
    return OK;
}

// 制空线性表
Status ClearList(List& L) {
    L.length = 0;
    return OK;
}

// 打印线性表
void PrintList(List L) {
    for (int i = 0; i < L.length; i++) {
        cout << L.elem[i] << " ";
    }
    cout << endl;
}

// 查找元素是否存在于线性表中, 有则返回位置(工具函数)
Status LocateElem(List& L, Elemtype e) {
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

// 查找元素是否存在于线性表中, 有则返回位置(可能有多个相同元素)
Status LocateElem2(List& L, Elemtype e, int answer[], int& count) {
    count = 0;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            answer[count++] = i + 1;
        }
    }
    return OK;
}

// 获取线性表中第i个位置的元素
bool GetElem(List& L, int i, Elemtype& e) {
    if (i < 1 || i > L.length) {
        return false;
    }
    e = L.elem[i - 1];
    return true;
}

// 删除线性表中第i个位置的元素
Status DeleteElem(List& L, int i, Elemtype& e) {
    if (i < 1 || i > L.length) {
        return false;
    }
    e = L.elem[i - 1];
    for (int j = i; j < L.length; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return e;
}

// 删除线性表中e的元素(可能会有多个相同e)
Status DeleteElem2(List& L, Elemtype e) {
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            DeleteElem(L, i + 1, e);
            i--;
        }
    }
    return OK;
}

// 在线性表最后添加元素
bool ListAppend(List& L, Elemtype e) {
    if (L.length >= MAXSIZE) {
        return false;
    }
    L.elem[L.length++] = e;
    return true;
}

// 插入元素
bool ListInsert(List& L, int i, Elemtype e) {
    if (i < 1 || i > L.length + 1 || L.length >= MAXSIZE) {
        return false;
    }
    for (int j = L.length; j >= i; --j) {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i - 1] = e;
    L.length++;
    return true;
}

// 无序合并: 将L2中的元素插入到L1中
void unionList(List& L1, List L2) {
    Elemtype e;
    for (int i = 0; i < L2.length; i++) {
        GetElem(L2, i + 1, e);
        if (!LocateElem(L1, e)) {
            ListInsert(L1, L1.length + 1, e);
        }
    }
}

// 有序合并: 合并两个有序表到L3, 并从小到大排序
void MergeList(List L1, List L2, List& L3) {
    InitList(L3);
    int i = 1, j = 1, k = 0;
    Elemtype e1, e2;
    while (i <= L1.length && j <= L2.length) {
        GetElem(L1, i, e1);
        GetElem(L2, j, e2);
        if (e1 <= e2) {
            ListInsert(L3, ++k, e1);
            i++;
        }
        else {
            ListInsert(L3, ++k, e2);
            j++;
        }
    }
    while (i <= L1.length) {
        GetElem(L1, i, e1);
        ListInsert(L3, ++k, e1);
        i++;
    }
    while (j <= L2.length) {
        GetElem(L2, j, e2);
        ListInsert(L3, ++k, e2);
        j++;
    }
}

// 冒泡排序
void BubbleSort(List& L) {
    for (int i = 0; i < L.length - 1; i++) {
        for (int j = 0; j < L.length - i - 1; j++) {
            if (L.elem[j] > L.elem[j + 1]) {
                Elemtype temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
}

int main() {
    List La, Lb;
    InitList(La);
    InitList(Lb);

    int x;

    cout << "输入La中的元素(以-1结束):" << endl;
    while (cin >> x && x != -1) {
        ListAppend(La, x);
    }

    cout << "输入Lb中的元素(以-1结束):" << endl;
    while (cin >> x && x != -1) {
        ListAppend(Lb, x);
    }

    Elemtype e;
    cout << "输入要查询的元素: ";
    cin >> e;
    int a[MAXSIZE], count;
    if (LocateElem2(La, e, a, count)) {
        cout << "存在, 位置: ";
        for (int i = 0; i < count; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "元素不存在" << endl;
    }

    cout << "输入要插入的元素和位置: ";
    int i;
    cin >> e >> i;
    cout << (ListInsert(La, i, e) ? "插入成功" : "插入失败") << endl;

    cout << "输入要删除的元素: ";
    cin >> e;
    cout << (DeleteElem2(La, e) == OK ? "删除成功" : "删除失败") << endl;

    cout << "La的当前元素: ";
    PrintList(La);

    List L3;
    MergeList(La, Lb, L3);
    cout << "有序合并后的L3: ";
    PrintList(L3);

    cout << "合并后的La: ";
    unionList(La, Lb);
    PrintList(La);



    BubbleSort(La);
    cout << "冒泡排序后的La: ";
    PrintList(La);

    // 对La进行制空
    ClearList(La);

    // 对Lb进行删除
    DestroyList(Lb);
    return 0;
}
