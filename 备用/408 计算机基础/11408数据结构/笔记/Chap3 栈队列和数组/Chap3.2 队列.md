# Chap2 队列

## 1.队列的基本概念

###### **1.队列的定义**

队列(Queue)也称作队,是**操作受限的线性表**,仅允许在表的一端进行插入,表的另一端删除

>   队列的操作特性为FIFO先进先出

###### **2.队列的基本操作**

```C++
InitQueue(&Q):	// 初始化队列
QueueEmpty(&Q):	// 判断队空
EnQueue(&Q,x):	// 入队操作,若队列未满,将x加入队尾
DeQueue(&Q,&x):	// 出队操作,若队列非空,删除队首元素
GetHead(Q,&x):	// 读取队首元素但不出队
```

## 2.队列的顺序存储结构

**队首指针指向队首元素,队尾指针指向队尾元素的下一个位置**

```C++
#define MaxSize 50
typedef struct{
  	ElemType data[MaxSize];
  	int front,rear;
}SqQueue;
```

>   **<font color=red>初始化:`Q.font = Q.rear =0`</font>**
>
>   **入队操作:当队列未满时,先将元素存入队尾,然后队尾指针+1**
>
>   **出队操作:当队列未空时,先取出队首元素,然后队首指针+1**
>
>   (队列只能判空(`Q.front = Q.rear = 0`)无法判满,可以假溢出)

## 3.循环队列

普通队列已经从物理上判死刑了(避免假溢出),所以引入循环队列(取模运算`%`)

###### **1.循环队列的ADT**

```C++
"初始状态":		Q.font = Q.rear = 0;
"队首指针进1":  Q.font = (Q.font + 1) % MaxSize;
"队尾指针进1":  Q.rear = (Q.rear + 1) % MaxSize;
"队列长度":		(Q.rear+MaxSize-Q.front) % MaxSize;
"出入队操作":	"目前统一按照顺时针方向移动"
```

**Q:循环队列中使用`Q.front == Q.rear`无法确定队空/队满**

Solution(1):牺牲一个存储单元作为头结点

>   队空:`Q.front == Q.rear;`
>
>   队满:`(Q.rear + 1) % MaxSize == Q.front;`
>
>   队列中元素个数:`(Q.rear - Q.front + MaxSize) % MaxSize`

Solution(2):计数(最简单)

>   队空:`Q.size = 0`
>
>   队满:`Q.size = MaxSize;`
>
>   队列中元素个数:`Q.size`

Solution(3):增加标志位(最简单)

>   队空:如果`flag==0`(无入队)并且`Q.front == Q.rear`
>
>   队满:如果`flag==1`(有入队)并且`Q.front == Q.rear`

###### **2.循环队列的基本运算**

```C++
typedef struct{
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}
// 加上const避免全量粘贴
bool QueueEmpty(const SqQueue Q) {
    return Q.front == Q.rear;
}
bool QueueFull(const SqQueue Q) {
    return (Q.rear + 1) % MaxSize == Q.front;
}
int QueueSize(const SqQueue Q) {
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}
bool EnQueue(SqQueue &Q,ElemType x) {   // 默认入队少一个元素做哨兵节点
    if ((Q.rear + 1)%MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize; // 不能单纯增加1否则假溢出
    return true;
}
bool DeQueue(SqQueue &Q,ElemType &x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}
```

## 4.队列的链式表示

###### **1.链队的ADT**

```C++
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
// 更简化的写法:同时声明了一个带有头尾指针的结点
typedef struct{
    LinkNode *front,*rear;
}LinkeQueue;
```

###### **2.链队的基本运算(注意出队最后一个元素)**

```C++
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
// 更简化的写法:同时声明了一个带有头尾指针的结点
typedef struct{
    LinkNode *front,*rear;
}LinkQueue;
// 注意:以下运算是带头节点的尾插法(front始终指向头节点,rear指向尾结点)

void InitQueue(LinkQueue &Q){
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
    // Q.front=Q.rear=new LinkNode;
    Q.front->next=NULL;
    // Q.rear=Q.front; 王道上面没有加上
}
bool QueueEmpty(const LinkQueue &Q){
    // return Q.front->next==NULL; 应该也可以
    return Q.front==Q.rear;
}
int QueueLength(LinkQueue &Q){ // 带头节点
    int len=0;
    LinkNode *p = Q.front->next;
    while (p){
        len++;
        p=p->next;
    }
    return len;
}

bool EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
    if (!s) return false;
    s->data=x;
    s->next = Q.rear->next;
    Q.rear->next=s;
    Q.rear = s;
    return true;
}

bool DeQueue(LinkQueue &Q,ElemType &x){
    if (Q.front == Q.rear)
        return false;
    LinkNode *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)     // 关键:如果删最后一个元素,rear可能野指针
        Q.rear = Q.front;
    free(p);
    return true;
}
```

## 5.双端队列

**"普通的栈是这世界上约束最强的线性结构（卡特兰数 $C_n$）"**

###### **1.双端队列**

双端队列是一种允许在两端进行插入和删除的线性表

入队(1):前端入队:插入的元素 排在后端插入的元素之前

入队(2):后端入队:插入的元素 排在前端插入的元素之后

出队:总是先出队列两端的元素,FIFO和FILO都不适用

###### **2.单侧受限的双端队列**

输出受限的双端队列:一端输入输出,另一端仅入队

输入受限的双端队列:一端输入输出,另一端仅出队

底部相邻的栈:如果规定从一端输入并还要从该端输出,则划分为了两个底部相邻的栈

考题(1):给定输入序列,判断输出序列合法性

考题(2):给定受限条件,计算一端的输出可能(栈)和不可能性(n!-卡特兰数)

## 6.本章试题

DBDBD CBCAD AAAAD DABCC DACD

DBDBD CBDCA DBAAD DABCC BACD

错的较多的是队首指针和队尾指针确定的循环队列:
**<font color=red>不要应激看到空是求模公式,大多数是front==rear</font>**

1.假设用数组Q[MaxSize]实现循环队列,队首指针front指向队首元素的前一位置,队尾指针rear指向队尾元素,则判断该队列为空的条件是(D,错选A)

A.Q.rear\==(Q.front+1)%MaxSize
B.(Q.rear+1)%MaxSize\==Q.front+1
C.(Q.rear+1)%MaxSize\==Q.front
D.Q.rear\==Q.front

2.假设用数组A[0...n]实现循环队列,队首指针front指向对队首元素的前一位置,队尾指针rear指向队尾元素,用(rear+1)%(n+1)\==front作为队满标志,则(A,错选D,不该错)
A.可用front==rear作为队空标志
B.队列中最多可有n+1个元素
C.可用front>rear作为队空标志
D.可用(front + 1)%(n+1)=rear

**<font color=deeppink>看到font和rear应激求模了,就事论事空就是front=rear</font>**

***

3.假设循环队列Q[MaxSize]的队首指针为front,队尾指针为rear,队列的最大容量为MaxSize,此外该队列再没有其它数据成员,则判断该队列已满的条件是(C,错选A)
A.Q.front == Q.rear
B.Q.front+Q.rear>=MaxSize
C.Q.front\==(Q.rear+1)%MaxSize
D.Q.rear\==(Q.front+1)%MaxSize

**<font color=deeppink>没有说就是牺牲一个存储单元,A是队空,C是队满</font>**

***

4.和顺序队列相比,链式队列的(A,错选D)
A.优点是队列的长度不受限制
B.优点是入队和出队的时间效率更高
C.缺点是不能进行顺序访问
D.缺点是不能根据队首指针和队尾指针计算队列长度 ->其实是O(1)



**评价一个链表适不适合做队列唯一的核心指标是：**
<font color=deeppink>它能否在 $O(1)$ 时间内同时找到队头（用于出队）和队尾（用于入队)</font>

5.下列描述的几种链表中,最适合用作队列的是(A,虽然说循环有限,但是非循环链表也可以无限长,并且按道理来说非循环链表可用接任意元素,循环单链表回覆盖队列中的元素(B)
A.带队首指针和队尾指针的循环单链表
B.带队首指针和队尾指针的非循环单链表
C.只带队首指针的非循环单链表
D.只带队首指针的循环单链表

6.下列描述的几种链表中,最不适合用作链式队列的是(A)
A.只带队首指针的非循环双链表 ->删除O(1),入队从front开始遍历
B.只带队首指针的循环双链表 -> 直接用next和prev
C.只带队尾指针的循环双链表 -> 直接用next和prev
D.只带队尾指针的循环单链表 -> 直接rear后面插

***

(2011)循环队列存储在一维数组A[0...n-1]中,且队列非空的时候front和rear分别指向队首元素和队尾元素,若初始队列为空,且要求第一个进入队列的元素存储在A[0]处,则初始时front和rear的值分别是(0,n-1)

>   所以rear指向元素,是有值的,需要先移动指针后放数据
>
>   ->所以rear初始要放在n-1,第一个元素才是0

只想到了入队,没有回顾条件:为什么不是(n-1,n-1)?两个指针指向同一个位置没有问题,我想的是front是n-1不变,rear指向下一个位置0然后插入,这样每次的入队都是统一的,空了一个n-1作为哨兵节点->如此front指向的永远是[n-1]而不是A[0]
