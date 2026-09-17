# Chap2.2 线性表的顺序表示

## 1.顺序表的定义

**顺序表:用一组地址连续的存储单元依次存储线性表的数据元素(逻辑和物理位置都相邻)**

>   **<font color=red>顺序表的特点:逻辑顺序和物理存储顺序完全一致->可以使用索引直接访问,O(1)时间</font>**
>
>   设其实存储地址为:LOC(A),存储结构为:==$$LOC(A)+(n-1)\times sizeof(Elemtype)$$==
>
>   (注:元素的位序从1开始,数组的元素下标从0开始,注意n-1)

顺序表的优点(1):==随机访问==,通过首地址和元素序号在O(1)时间内找到指定元素

顺序表的优点(2):存储密度高,每个节点仅存储数据元素

顺序表的缺点(1):插入和删除效率低,需要移动大量元素

顺序表的缺点(2):要求分配连续的存储空间

## 2.顺序表基本操作的实现

顺序表的实现:只有data数组和length,所以使用索引进行访问

链表的实现:存在data和next指针,所以使用`ptr = ptr -> next`实现

**1.顺序表的初始化(InitList):静态只有Length,动态需要对data进行malloc初始化**

```c++
#define MaxSize 10
typedef struct{
	Elemtype data[MaxSize];
    int length;
}SqList; // 类型名称
void InitList(SqList &A){
    A.length = 0; 
}
int main(){
    SqList L;
    InitList(L);//编译器可能会也可能不会自动初始化,可能有脏数据
    return 0;
}
```

```c++
#define MaxSize 10
#include<stdlib.h>
typedef struct{
	Elemtype *data;
    int MaxSize;
    int length;
}SqList; // 类型名称

void InitList(SqList &L){
    // malloc其实返回的是一个指向连续空间的"指针",所以需要*data
	L.data = (Elemtype*)malloc(sizeof(ElemType)*InitSize);
    L.length = 0;
    L.MaxSize = InitSize;
	// 当然可以new和delete
}
void IncreaseSize(SqList &L,int len){
    int *p = L.data;
    L.data = (int*)malloc((L.MaxSize+len)*sizeof(Elemtype));
    for(int i = 0;i<L.length;i++){
        L.data[i] = p[i];
    }
    L.MaxSize = L.MaxSize + len;
    free(p);
}
```

**2.插入操作(ListInsert):需要判断边界,然后for循环,最后返回是否插入成功(bool)**

最好情况:不需要移动元素O(1);最坏情况:需要移动所有元素O(n)

平均情况:有n+1个位置可以插入,平均移动次数:$\frac{1}{n+1}\frac{n(n+1)}{2} = \frac{n}{2}$==(0,1,...,n)==

边界(1):插入位置是否合法

边界(2):插入后的大小是否超过MAXSIZE

```C++
bool ListInsert(SqList &L,int i,int &e){
    // 这里可能验证i是否是让之前已存在的内容连续
    if(i<1 || i>L.length+1)return false;
    if(L.length >= MaxSize)return false;
    for(int j = L.length;j>=i;j--)
        L.data[j] = L.data[j-1];
    L.data[i-1] = e;
    L.length++;
    return true;
}
int main(){
	SqList L;
    InitList(L);
}
```

**3.删除操作(ListDelete):需要判断边界,然后for循环,最后返回是否删除成功(bool)**

最好情况:不需要移动元素O(1);最坏情况:需要移动其余n-1个元素O(n)

平均情况:有n个元素可以删除,平均移动次数:$\frac{1}{n}\frac{n(n-1)}{2} = \frac{n-1}{2}$==(0,1,...,n-1)==

边界(1):删除位置是否合法(同时删除操作是否合法)

```C++
bool ListDelete(SqList &L,int i,int &e){
    if(i<1 || i>L.length+1)return false;
    e = L.data[i-1];
    for(int j=i;j<L.lengthl;j++)
        L.data[j-1] = L.data[j];
    L.length--;
    return true;
}
int main(){
    ListDelete(L,3,e);
}
```

**5.按位查找(GetElem)**

最好情况:直接通过索引找到目标元素,时间复杂度$O(1)$

```C++
ElemType GetElem(SqList L,int i){
    // 当然可以对i进行检查
    return L.data[i-1];
}
// 这里data是SeqList类型->	base location+n*(sizeof(SeqList))
// 如果定义int *p->			 base location+n*(4)
```

**4.按值查找(LocateElem):直接for循环,返回位次(从1开始)**

最好情况:直接找到目标元素O(1);最坏情况:需要遍历n个元素O(n)

平均情况:有n个元素可以查找,平均查找次数:$\frac{1}{n}\frac{n(n+1)}{2} = \frac{n+1}{2}$

```c++
int LocateELem(SqList L,TypeName e){
    for(int i=0;i<L.length;i++)
        if(L.data[i]==e)
            return i+1; // 返回的是位序而不是index
    return 0;// 没找到
}
```

## 3.题目

**<font color=red>随机存取:并非随机的进行存取,而是查找序号为i元素的时间和顺序表个数n无关**

ACCBB CCCCC CDD

ACCBD ACCCC CDD

**1.若线性表最常用的操作是存取第i个元素及其前驱和后继元素的值,提高效率应该采用?**

**2.若线性表最常用的操作是存取任意一个指定序号的元素并在最后进行插入删除,应采用?**

两个的答案都是顺序表,链表不支持直接的索引访问,导致O(n)