# p2.3 线性表的链式表示

## 1.单链表的定义

前提:顺序表支持随机存取元素,**但插入和删除元素需要移动大量元素**

结果:链式存储不要求连续的存储单元,插入和删除元素只需修改指针,**但是无法随机存取**

**单链表:线性表的链式存储,通过一组==任意的存储单元==,来存取线性表中的元素**

>   链表结点:元素自身的信息(data)+指向后继结点的指针(next)
>
>   额外提醒:即数据域+位于堆(malloc)的next指针(存放的是链接地址)
>
>   **所以链式的任意存储单元也是有代价的(额外的指针空间),是非随机存储的存储结构</font>**

```C++
// ADT
typedef struct LNode{
    Elemtype data;
    struct LNode *next;
}LNode,*LinkList;
// 后序(1):指针	使用LinkList L强调这是链表
// 后序(2):指针	LNode *p 强调这是个结点指针
```

>   通常使用一个头指针p指向链表的起始位置:`LNode *p = L;`
>
>   不带表头节点的单链表:用`L->next==nullptr`和`L->data`的时候表示链表为空
>
>   带表头节点的单链表:仅用`L->next==nullptr`的时候表示链表为空

**头指针和头结点的关系**

头指针一直存在,位置始终指向第一个结点(头节点or首元结点)

头结点可能存在,由具体的实现方式决定

>引入头结点的优点(1):操作统一性,首元结点和其它结点的插入删除操作一致
>
>引入头结点的优点(2):空表操作统一,避免额外讨论`L->data`是否为空

首元结点一直存在,它是第一个含有实际数据的结点

## 2.单链表上的基本操作

注意:前插/后插/前删/后删指->前不找前驱,后表示找前驱

>   ->在第i个位置插入:需要遍历O(n)->后插法
>
>   ->在已知的p结点之前插入一个新结点:直接插入O(1)->前插法

注意(2):头插/尾插指->通过头指针建立(自带ptr),通过尾指针建表(新增ptr)

###### **1.单链表的初始化**

```c++
// 1.带有头结点的初始化
bool InitList(LinkList &L){
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    return true;
}
// 2.不带头结点的初始化
bool InitList(LinkList &L){
    L = NULL;
    return true;
}
```

>   注:p是指向链表结点的指针,则*p可以表示结点本身
>
>   数据:`p->data`或者`(*p).data`/`p->next->data`或者`(*(*p).next).data`

###### **2.求表长(`O(N)`)**

**从头结点开始**==(因为可能不存在首元结点)==求表长指统计表中数据结点的个数

```c++
int Length(LinkList L){
	int len = 0;
    LNode *p = L;
    whiler(p->next != NULL){
    	p=p->next;
        len++;
    }
    return len;
}
```

###### **3.按序号查找(`O(N)`)**

**从头结点开始**==(因为头结点算作第0个结点)==返回第i个结点的指针

```C++
LNode *GetElem(LinkList L,int i){
    if(i<0)return NULL;
    LNode *p = L;//初始化指针
    int j=0;
    while(p!=NULL && j<i){
        p=p->next;
        j++;
    }
    return p;
}
```

###### **4.按值查找(`O(N)`)**

**从首元结点开始**==(因为首元结点才有数据)==返回和定值e相同的结点指针->是链表

```C++
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L->next; // 首元结点
    while(p!=NULL&&p->data!=e){
        p=p->next;
    }
    return p;
}
```

###### **5.后插法插入结点操作(`O(N)`)(在i-1插入后连指针)**

目的:将值为e的新结点插入到第i个位置->检查i的合法性,以i-1为前驱进行插入

>   **整体而言操作是`O(N)`(查找pre指针位置),但是单纯插入操作是`O(1)`**

```c++
bool ListInsert_post(LinkList &L,int i,ElemType e){
    LNode*p=L;
    int j=0;
    while(p!=NULL&&j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL)return false;
    LNode *s = (LNode*)malloc(sizeof(LNode)); // C的写法
    // LNode *s = new ListNode(); // C++写法
    s->data = e;	
    s->next = p->next;	// 先连后
    p->next = s;		// 再连前
    return true;
}
// 如果不带有头指针,操作第一个元素还需要修改头指针
if(i==1){
	LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = L;
    L = s; // 修改头指针
    return true;
}
```

>如果先连前(`p->next=s`),再连后(`s->next=p->next`)等价于`s->next=s`循环

###### **6.前插法插入结点操作(`O(1)`)(在i处挤进去后交换数据,连指针)**

目的:将值为e的新结点插入到第i个位置->直接接入i后面->交换数据

>   **整体而言操作是`O(N)`,单纯插入操作是`O(1)`**

```c++
bool ListInsert_pre(LNode *p,Elemtype e){
	if (p == NULL) return false; 
    LNode *s = (LNode *)malloc(sizeof(LNode)); 
    if (s == NULL) return false; // 内存申请失败
    s->next = p->next; 
    p->next = s;       
    s->data = p->data; 
    p->data = e;      
    return true;
}
```

>如果先连前(`p->next=s`),再连后(`s->next=p->next`)等价于`s->next=s`循环

###### **7.后删法删除结点`O(N)`**(p指向i-1,q指向i,p连接,删q)

目的:删除第i个结点并将其元素由e带出

```C++
bool ListDelete_post(LinkList &L,int i,Elemtype &e){
    if (i < 1) return false;
    LNode *p=L;
    int j=0;
    while(p!=NULL&&j<i-1){
        p = p->next;
        j++;
    }
    if(p->next==NULL||j>i-1)return false; // 在i-1没找到或者已经到链尾
    LNode *q=p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}
```

###### **8.前删法删除结点`O(1)`**(p指向i,q指向i+1,p连接,换数据,删q)

**<font color=red>唯一带坑的,不能删除尾结点(没有后继)</font>**

```c++
// 只有在这种特定限制条件下，这个方法才是"神技"
bool ListDelete_post(LNode *p) {
    if (p == NULL || p->next == NULL) {
        return false; // 无法处理尾结点，这是算法本身的局限
    }
    LNode *q = p->next; 
    p->data = q->data;  
    p->next = q->next;
    free(q);
    return true;
}
```

###### **9.头插法建立单链表(插入一个O(1),插入n个O(n))**

由于L指针不变,所以新添的都在前面,符合FILO,栈

**->所以遇到链表==原地逆置/大数低位相加==,直接用头插法插回去即可**

```C++
LinkList List_HeadInsert(LinkList &L){
    int x;
    LNode *s; // 野指针
    L = (LNode*)malloc(sizeof(LNode));
    L ->next = NULL;	// 好的习惯
    scanf("%d",&x);
    while(x!=9999){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next; // 先插后
        L->next = s		   // 再插前
        scanf("%d",&x);	   // 注意&
    }
    return L;
}
```

###### **10.尾插法建立单链表(插入一个O(1),插入n个O(n))**

由于s指针向后移动,所以新添的都在后面,符合FIFO,队列

**->所以遇到合并有序链表,使用尾插法**

```C++
LinkList List_TailInsert(LinkList &L){
    int x;
    L = (LNode*)malloc(sizeof(LNode));
    LNode *s,*r = L; //双指针(野指针+尾指针)
    scanf("%d",&x);
    while(x!=9999){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;	// r=r->next也可以吧
        scanf("%d",&x); // 注意&
    }
    r ->next = NULL;//最后一定要设置NULL
    return L; 
}
```

## 3.双链表(课本无代码)

前提:单链表的每个结点仅包含一个指向后继的指针,只能前往后遍历

结果:双链表的每个结点包含prior和next指针

四个指针:`p->next`,`s->prior`,`s->next`,==`s->next->prior`(可能不存在)==

**<font color=red>隔山打牛必须验空:`p->next->prior`和`p->next->next`等</font>**

```C++
// ADT
typedef struct DNode{
    Elemtype data;
    struct DNode *prior,*next;
}DNode,*DLinkList;
// 初始化
bool InitDLinkList(DLinkList &L){
 	L = (DNode *)malloc(sizeof(DNode));
    if(L==NULL)
        return false;
    L->prior = NULL;	// 好习惯
    L->next = NULL;		// 好习惯
    return true;
}
```

###### **1.后插法双链表的插入操作(已知`DNode *p`)**

```C++
bool ListInsert_post(DNode *p,Elemtype e){
    if(p==NULL)return false;
	DNode *s = (DNode*)malloc(sizeof(DNode));
    if(s==NULL) return false;
    s->data = e;
    // (1)先连s(先右)
  	s->next = p->next;
    s->prior = p;
    // (2)再连可能存在的
    if(p->next!=NULL){
        p->next->prior =s;
    }
    // (3)最后改p->next(最后!!!)
    p->next = s;
    return true;
}
```

###### **2.前插法双链表的插入操作(已知`DNode *p`)**

特点是存在prior指针,不需要换数据了

>   单链表:在i处新建s,在i处连接,把i+1换成旧数据,把i换成新数据
>
>   双链表:在i处新建s,通过i->prior连接s即可

```C++
bool ListInsert_pre(DNode *p,Elemtype e){
	if (p==NULL||p->prior==NULL) return false; // 注意头结点要存在
	// DNode *s = new DNode();
	DNode *s = (DNode*)malloc(sizeof(DNode));
    if(s==NULL) return false;
    s->data = e;
    // (1)先连s(先右)
    s->prior = p->prior;
    s->next = p;
    // (2)再连指向s的(必存在)
    p->prior->next =s;
    p->prior = s;
    return true
}
```

###### **3.后插法双链表的删除操作(已知`DNode *p`和`DNode *q`,q在p后)**

```C++
bool ListDelete_post(DNode *p, DNode *q, Elemtype &e){
    if(p==q||p==NULL||q==NULL) return false;
    e = q->data;
    // (1)先接
    p->next = q->next; 
    if(q->next != NULL){ 
    	q->next->prior = p; 
    }
    // (2)后删
	free(q);
    return true;
}
```

###### **4.前插法双链表的删除操作(已知`DNode *p`和`DNode *q`,q在p前)**

```C++
bool ListDelete_pre(DNode *p,DNode *q,Elemtype &e){
    if(p==q||p==NULL||q==NULL)return false;
    if(q->prior==NULL)return false; // 额外:头节点数据都没有
    e = q->data;
    // (1)先接
 	p->prior = q->prior;
    q->prior->next = p;
    // (2)后删
	free(q);
    return true;
}
```

###### **5.遍历操作**

```C++
// 后向遍历
while(p!=NULL){p=p->next;}
// 前向遍历
while(p!=NULL){p=p->prior;}
// 前向遍历(除了头节点)
while(p->prior!=NULL){p=p->prior}
```

## 4.循环链表

**<font color=red>不再设置头指针,而是设置尾指针,这样前插后插都是`O(1)`</font>**

>   循环单链表的唯一痛点:**尾删要前驱结点,要`O(N)`**->头插/头删/尾插`O(1)`

###### **1.循环单链表**

前提:单链表的结尾是NULL

结果:循环链表的结尾是头结点(注意不是**首元结点**)

>   判空条件:不再是`L->next = NULL;`,而是`L->next=L;`
>
>   ```C++
>   LNode *p = L->next; // 从首元结点开始
>   while (p != L) {    // 没绕回到头结点就继续
>       // ...
>       p = p->next;
>   }
>   ```

###### **(可选)2.循环单链表的组合`(O(1))`**

步骤(1):表A的头节点:`p = LA->next`

步骤(2):表A的next接表B的首元:`LA->next = LB->next->next`

步骤(3):表B的尾巴接入A的头结点:`LA->next = p`

步骤(4):表B的头节点释放:`free(LB->next)`

###### **3.循环双链表**

在循环单链表的基础上双向(prior和next)

>   判空条件:不再是`L->next = NULL;`,而是`L->next=L;L->prior=L;`

```C++
// 插入操作
bool InsertNextDNode(DNode *p,DNode *s){
    s->next = p->next;
    p->next->prior=s;
    s->prior=p;
    p->next=s;
}
```

## 5.静态链表

**定义:静态链表是用数组模拟线性表的链式存储结构,包括`data域`和`next域`**

>   也就是说不再通过`struct LNode *next;`指针来移动,而是index
>
>   **需要模拟malloc:从备用链表中摘下一个结点O(1)**
>
>   **需要模拟free:将被删除的结点插回备用链表O(1)**
>
>   ==虽然使用了数组,但是不支持随机存储,**需要从头节点一个个找**==
>
>   **<font color=red>固定长度!!已经定死了!!</font>**

```c++
// ADT
#define MaxSize 50
typedef struct{
    ElemType data;
    int next;	// 使用next==-1表示NULL
    // 注意这里其实是链接地址
}SLinkList[MaxSize]; // 相当于每次新建一个MaxSize大小的静态链表
```

>   出现目的(1):有些编程语言(Basic)不支持指针
>
>   出现目的(2):内存地址固定不允许动态分配的嵌入式系统

```C++
// 初始化:把next置为-1即可
// 查找:相当于链表O(n),向后查找
// 插入:随便找一个空的表位置插入元素,只不过要修改i-1和插入结点的链接地址
```

## 6.顺序表和链表的比较

###### **1.存取(读写)方式**

顺序表:支持随机存取->可以通过下标直接访问;支持顺序存取->从开始遍历

链表:仅支持顺序存取->从开始遍历

###### **2.逻辑结构和物理结构**

顺序表(顺序存储):逻辑结构和物理内存一致:都是连续存放

链表(链表存储):逻辑结构和物理内存不一致:需要指针维护

###### **3.查找,插入,删除操作**

按值查找:无序表($O(n)$),**有序表**(==$O(log_2n)$二分查找==)

按序查找:顺序表($$O(1)$$),链表($$O(n)$$)

插入删除:顺序表($$O(n)$$),链表($$O(1)$$)

###### **4.空间分配**

顺序表:需预先设定容量,静态容易浪费/溢出,动态要复制所有数据,效果差

链表:动态结点实时分配,按需扩展,每个结点需要存储指针域,**存储密度<1**

###### **5.实际选择**

(1)基于存储的考虑:空间能否确定?能否接受存储密度<1

(2)基于运算(操作)的考虑:(大量按序访问?->顺序表)(大量增删操作?->链表)

(3)基于环境的考虑:高级语言是否支持指针

| **维度**               | **顺序表 **                                                  | **链表 **                                                    |
| :--------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **存储结构**           | 连续存储                                                     | 非连续存储                                                   |
| **存储密度**           | =1(最高,100%用于存数据)                                      | <1(低,需要额外空间存指针next/prior)                          |
| **硬件亲和性**         | Cache友好(空间局部性好，预取命中率高)                        | Cache不友好 (跳跃访问易导致Cache Miss)                       |
| **内存分配**           | 静态(栈上/全局，易溢出)<br>动态(堆上，扩容需搬家)            | 动态(堆上，按需分配只要内存够就不溢出)                       |
| **度量公式 (查找)**    | $T(n) = O(1)$ (按位)<br>$T(n) =O(n)$ (按值，有序可$O(\log n)$) | $T(n) = O(n)$ (无论按位还是按值)                             |
| **度量公式 (插入/删)** | $T(n) = O(n)$ (平均移动$n/2$个元素)                          | $T(n) = O(n)$ (已知位置,需要遍历)<br>$T(n) = O(1)$ (已知指针,无需遍历) |

基本上顺序表只有查上面具有优势

回答问题:逻辑结构是什么+存储结构是什么样的+基本操作时间复杂度
