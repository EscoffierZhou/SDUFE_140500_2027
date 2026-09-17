# Chap3.1 栈

## 1.栈的基本概念

###### **1.栈的基本性质概念**

**栈:仅允许在一端进行插入和删除的线性表**(即栈的入栈和删除操作被限制在表的一端进行)

>   栈顶:允许进行插入和删除操作的一端
>
>   栈底:不允许进行插入和删除操作的一端
>
>   空栈:不含任何元素的栈

LIFO:后进先出($a_1,a_2,a_3,a_4,a_5$入栈,则$a_5,a_4,a_3,a_2,a_1$出栈)

**栈的逻辑结构:LIFO**

**栈的存储结构:顺序栈&链栈**

**栈的基本操作:**

```
InitStack(&S):		初始化空栈
StackEmpty(S):		判断栈是否为空,若栈S为空则返回true,否则false
Push(&S,x):			入栈操作:若栈未满,则x程序新的栈顶元素
Pop(&S,&x):			出栈操作:若栈非空,则弹出栈顶元素,并通过x返回该值
GetTop(S,&x):		读栈操作:读取栈顶元素但不出栈
DestroyStack(&S):	销毁栈S:释放其占用的内存空间
```

###### **<font color=red>2.栈的数学性质:卡特兰数(Catalan)</font>**

**卡特兰数:描述具有偏序限制的组合模型**

当n个不同元素**==按固定次序==**入栈时(前提失效直接死),可能的出栈序列总数为

```math
H_n= \frac{1}{n+1}C^n_{2n}
```

| n = 1 | $H_1=\frac{1}{1+1}C_2^1=\frac{1}{2}\frac{2}{1} = 1$          |
| :---: | :----------------------------------------------------------- |
| n = 2 | $H_2=\frac{1}{1+2}C_4^2=\frac{1}{1+2}\frac{4\times 3}{1\times 2}=2$ |
| n = 3 | $H_3=\frac{1}{1+3}C_6^3=\frac{1}{1+3}\frac{6\times 5\times 4}{1\times 2\times 3}=5$ |
| n = 4 | $H_4=\frac{1}{1+4}C_8^4=\frac{1}{1+4}\frac{8\times 7\times 6\times 5}{1\times 2\times 3\times 4}=14$ |
| n = 5 | $H_5=\frac{1}{1+5}C_{10}^5=\frac{1}{1+6}\frac{10\times 9\times 8\times7 \times 6}{1\times 2\times 3\times 4\times 5}=42$ |

推导(1):建模:起点(0,0),终点(n,n),限制:出栈次数不能多于入栈次数,不能触碰到$y=x+1$ 

推导(2):总路径:从(0,0)到(n,n)总共需要2n步(n向右n向上):$Total = C^n_{2n}$

推导(3):反射原理:(n,n)和(n-1,n+1)关于直线对称:$$Illegal=C^{n+1}_{2n} = C^{n-1}_{2n}$$

>   Insight:原本应该有2n步的,所以$C^n_{2n}$就刚刚好
>
>   -> $C^{n-1}_{2n}$就表示向上走了n-1,另一个向右自然走了n+1,所以无法到达正确的终点(n,n)
>
>   -> 实际意义就是少了一次入栈的同时还多了一次出栈

推导(4):化简

```math
C^{n}_{2n}-C^{n-1}_{2n} = \frac{(2n)!}{n!n!}-\frac{(2n!)}{(n-1)!(n+1)!}=\frac{1}{n+1}C^n_{2n}
```

###### **3.卡特兰数的应用(同构问题)**

**使用栈的卡特兰数/使用反射原理一定有要看前提条件,不然根本用不了**

>   <font color=red>如果不固定输入序列的次序,结果是n!(全排列)</font>

**(1)进出栈序列:求n个元素入栈,对应合法出栈的序列数:$\frac{1}{n+1}C^n_{2n}$**

**(2)进出栈序列(保留部分元素):求n个元素入栈,栈内剩了k个,求对应合法出栈的序列数**

>确定终点(n,n-k)->全部路程:$C^n_{2n-k}$或者$C^{n-k}_{2n-k}$->非法终点(n-k-1,n+1)
>
>最终结果:$H_n = C^n_{2n-k}-C^{n+1}_{2n-k}$

(3)二叉树形态计数:求n个结点可以构成多少种不同形态的二叉树:$\frac{1}{n+1}C^n_{2n}$

>   约等于知道前序遍历(入栈次序),问中序遍历(出栈次数)

(4)括号匹配问题:任何时候左右括号数量需要匹配:$\frac{1}{n+1}C^n_{2n}$

(5)凸n+2多边形通过互不相交的对角线切分成$n$个三角形，有$\frac{1}{n+1}C^n_{2n}$种切分法

###### **4.卡特兰数写序列(以adcb为固定顺序)**

1.求出卡特兰数:$H(n) = \frac{1}{1+4}\frac{8\times 7\times 6\times 5}{1\times 2\times 3\times 4} = 14$

2.写出字典序,要求从左往右数,I的累计数量必须大于等于O的累计数量,然后带入输入顺序

| IIIIOOOO | (adcb) | b,c,d,a |
| -------- | ------ | ------- |
| IIIOIOOO | (adc)b | c,b,d,a |
| IIIOOIOO | (adc)b | c,d,b,a |
| IIIOOOIO | (adc)b | c,d,a,b |
| ...      | ...    |         |

## 2.栈的顺序存储结构

###### **1.顺序栈的实现**

利用一组地址连续的存储单元存储从栈底到栈顶的数据元素,使用top指针指示

```C++
#define MaxSize 50
typedef struct{
    Elemtype data[MaxSize];
    int top;	// 使用数值
}SqStack;
```

栈顶指针:初始值设置为`S.top=-1` 栈顶元素:`S.data[S.top]`

入栈操作:**当栈未满**,先设置栈顶指针+1,然后存入元素

出栈操作:**当栈非空**,先取出元素,然后设置栈顶指针-1

判定栈空:`S.top==-1` 判定栈满`S.top==MaxSize-1`

(初始值为0,则栈空为`S.top==0`,栈满为`S.top=MaxSize`)

**<font color=red>反直觉(1):取出元素指的是栈顶指针不包含该元素,但是还可能通过溢出访问</font>**

**<font color=red>反直觉(2):-1和0会直接导致:-1指向栈顶元素,0则指向栈顶元素的下一个位置</font>**

###### **2.顺序栈的基本操作**

**1.初始化**

```C++
void InitStack(SqStack &S){
    S.top=-1;
}
```

**2.判断栈空**

```C++
bool StackEmpty(SqStack S){
    if(S.top==-1)
        return true;
    else:
        return false;
}
```

**3.入栈(`O(1)`)**

```C++
bool Push(SqStack &S,ElemType x){
    if(S.top==MaxSize-1)
        return false;
    S.data[++S.top]=x;
    // 如果初始化为0,则S.data[S.top++]=x
    return true;
}
```

**4.出栈(`O(1)`)**

```C++
bool Pop(SqStack &S,Elemtype &x){
    if(S.top==-1)
        return false;
    x = S.data[S.top--];
    // 如果初始化为0,则x = S.data[--S.top]
    return true;
}
```

**5.读取栈顶元素(`O(1)`)**

```C++
bool GetTop(Stack S,ElemType &x){
    if(S.top==-1)	
        return false;
    x=S.data[S.top];
    return true;
}
```

###### **3.顺序栈的变体:共享栈**

两个共享栈共享一个数组空间,`topA=-1,topB=MaxSize`

>   判满:`topB-topA=1`,表示两个栈顶元素相邻

## 3.栈的链式存储结构

**ADT**

```C++
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}*LiStack;
```

**头插法建立单链表(带头节点,错误的)**

```C++
bool InsertNextNode(LNode *p,Elemtype e){
    if(p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    s->data = e;
    s->next = p->next;
    p->next = a;
    return true;
}
```

**单链表的Push操作**

```c++
bool Push(LiStack &S, ElemType x) {
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    if (!p) return false; // 内存分配失败（注意 !p 才是分配失败）
    p->data = x;
    p->next = S; // 新节点的 next 指向当前的栈顶节点
    S = p;       // 栈顶指针 S 上移，指向这个新节点
    return true;
}
```

**单链表的Pop操作**

```c++
bool Pop(LiStack &S, ElemType &x) {
    if (S == NULL) return false; // 栈空，无法出栈
    LinkNode *p = S;
    x = p->data;     // 取出数据
    S = S->next;     // 栈顶指针 S 下移，指向下一个节点
    free(p);         // 释放原栈顶节点的内存（防止内存泄漏）
    return true;
}
```

## 4.本章错题

AABCD BAACD DACBA DDDCC ACBBB CDBDD D

BCBCB AAACC DABDA DDDCC ACCBA CDBCD D

**1.<font color=red>栈和队列都具有相同的逻辑结构:线性->指的是集合/线性/树形/图形</font>**

它们的逻辑结构相同,所以都有顺序和链式的实现方式
它们的ADT不同(逻辑结构:线性相同,操作集合:FIFO/LIFO)
它们的存储结构相同,但是具体的实现根据情况讨论,所以暂定不同
它们的运算(操作集合)不同

***

**2A.数组data[1..n]存储一个栈,初始栈顶指针top=1,元素x入栈的操作是:data[top++]=x;**

**2B.数组data[1..n]存储一个栈,初始栈顶指针top=n+1,元素x入栈的操作是:data[--top]=x;**

top=0才能实现先++然后存入的操作,否则top=1先++则第一个元素没有数值
top=n+1才能实现先--然后存入的操作,否则top=n先--则最后一个元素没有数值

***

**3.3个不同元素依次入栈,能得到5种不同的出栈序列**

满足使用卡特兰数的要求:不同+固定入栈顺序(这里依次)
真正的坑:3个不同元素在栈中进行任意的存取操作，能产生多少(6)种不同的出栈序列
如果是卡特兰数:$\frac{1}{n+1}C^3_6 = 5$
如果是全排列:$n!\times C_n= 6\times5 = 30$

**4.若栈的输入序列是$P_1,P_2,P_3.,..,P_n$,输出的序列是1,2,3,...,n,若$P_3=1$,则$P_1$的值是(C)**

A.可能是2 B.一定是2 C.不可能是2 D.不可能是3

>   $P_1\rightarrow P_2 \rightarrow P_3=1],\therefore P_3>P_2>P_1$,不可能是2

**5.若栈的输入序列是$P_1,P_2,P_3.,..,P_n$,输出的序列是1,2,3,...,n,若$P_3=3$,则$P_1$的值是?(A)**

A.可能是2 B.不可能是1 C.一定是1 D.一定是2

>   $P_1\rightarrow P_2 \rightarrow P_3=3],\therefore P_3>P_2>P_1$,可能是1

***

**6.已知栈的入栈序列是1,2,3,4,出栈顺序为$P_1,P_2,P_3,P_4$,则$P_2,P_4$不可能是(4,3)**

>假设$P_2=4$,则后序必然按照3,2,1出栈->又$P_4=3$,中间必死

**7.(2013真题)一个栈的入栈序列是1,2,3,...,n,出栈顺序为$P_1,P_2,...P_n$,若$P_2=3$,则$P_3$可能的取值个数是?n-1**

>   (旧:对于4个数我认为应该只有3种,放入1出来1然后放入2出来3;放入1放入2出来2出来3,放入1放入2放入3放入4出来4出来3,然后选出来的n-1)
>
>   新:$P_2=3$出栈了,所以比3小的2和1会在$P_3$受限,但是前面也可以都出去,所以仅排除本身即可

<font color=red>**题型(1):输出序列是固定的,问输入序列$P_i$的可能情况**</font>

>trick:输出是单调递增的,所以任何时刻,从栈顶到栈底必须严格单调递增

<font color=red>**题型(2):输入序列是固定的,问输出序列$P_i$的可能情况**</font>

>trick:输入是升序的,则输出序列中:a...b...c,a>c>b必死
>
>**一个大数出栈后，所有比它小的且还没出栈的数，必须严格按照从大到小的顺序依次出栈。**

***

**8.设栈的初始状态为空,当字符序列为"n1_"作为栈的输入,输出长度为3,可以用作C语言标识符的序列有(3)个**

>   按照卡特兰数其实应该有5个,**C语言不能以数字开头**
>
>   ```
>   n 1 _
>   n _ 1
>   _ 1 n
>   1 n _
>   1 _ n
>   ```

***

**9.设有一个顺序共享栈Share[0:n-1],其中第一个栈顶指针top1的初值为-1,第二个栈顶指针top2的初值为n,则判断共享栈满的条件是(`top2-top1=1`)**

>   -1,所以需要data[++top1]
>
>   n,所以需要data\[--top2]
>
>   但是无论如何都是top2-top1=1(相邻位)