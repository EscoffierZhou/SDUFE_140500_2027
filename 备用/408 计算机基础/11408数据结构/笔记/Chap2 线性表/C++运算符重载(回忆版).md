# C++运算符重载

## 1.this

**this指针:当一个成员函数被调用时，this指针指向"当前正在操作的那个对象的隐式指针。**

>   本质上是`{Struct_name}* const`,比如`SqList* const`
>
>   作用于:类的非静态成员函数中(**static**函数里面是没有this的)

this的作用(1):解决名称冲突(成员变量和函数形参名称一样)

```C++
struct Student{	int id;
  	void SetID(int id){
        this->id = id // 左边是对象,右边是函数形参
    }
}
```

this的作用(2):链式调用(`L.insert(a).insert(b).insert(c)`)

```C++
SqList& addElement(ElemType e) {
    this->data[this->length++] = e;
    return *this; // 返回当前对象的引用
}
```

## 2.结构体内部符号重载

**结构体内部重载的通用格式如下： `返回类型 operator 运算符 (参数列表) { ... }`**

```C++
#include <iostream>
struct Student {
    int id;
    int score;
    // const(1):参数里面:保证不修改被比较的对象
    // const(2):函数末尾:保证不修改成员变量
    bool operator == (const Student& other) const {
        return this->id == other.id; // 以学号作为判断标准
    }
};

#define MaxSize 10
typedef struct {
    Student data[MaxSize];
    int length;
} SqList;
void InitList(SqList &L) {
    L.length = 0;
}
int LocateElem(SqList L, Student e) {
    for (int i = 0; i < L.length; i++) {
        // 这里会自动调用 Student 结构体里重载的 ==
        if (L.data[i] == e) // 如果顺序表中的
            return i + 1;
    }
    return 0;
}

int main() {
    SqList L;
    InitList(L);
    // 模拟插入
    L.data[0] = {1001, 95};
    L.length = 1;
    Student target = {1001, 0}; // 即使成绩不同，只要 ID 对了就能找到
    int pos = LocateElem(L, target);
    if(pos) std::cout << "Found at position: " << pos << std::endl;
    return 0;
}
```

