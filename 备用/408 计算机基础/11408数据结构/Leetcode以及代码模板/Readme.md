# Leetcode以及代码使用说明

## 1.抽象层面(120+的关键)

###### **1.数据结构**

```
=================================================
【抽象层】ADT（逻辑结构 + 操作集合）
    ↓   
【实现层】存储结构（顺序/链式/索引/散列）
    ↓
【算法层】在特定结构上的算法（遍历/查找/排序/优化）
(1) 这是哪一层（ADT / 实现 / 算法）
(2) 这是必须操作还是实现技巧
(3) 如果换一种存储结构，这个结论还成立吗
=================================================
考场例子:在带头结点的单链表中删除值为x的结点
100:想指针、想边界、想空表 → 慌
120:ADT:Delete+实现:带头结点+算法:一次扫描
=================================================
强化阶段(1):(2个月,100+)看题不慌/这题在考什么
强化阶段(2):(4个月,110+)主观题有条理/推导不乱
强化阶段(3):(6个月,120+)体系基本固化/能抗干扰、抗陌生题
注:主观题分点+教材语言+不发明新概念
区分好:逻辑结构 vs 存储结构/算法 vs ADT
```

```
=================================================
Eg:二叉树中序遍历
工程:TreeNode放哪/递归还是非递归/能不能写成模板
考研:二叉树ADT中的基本操作/中序遍历在ADT中的地位是什么
=================================================
【ADT层】:基本操作集合
  定义：结点、左右子树
  基本操作：建树/判空/遍历
【实现层】:比如TreeNode
  顺序存储 vs 链式存储
  指针/数组
【算法层】:比如中序遍历
  递归遍历
  非递归遍历
  Morris遍历（实现技巧，不是 ADT）
=================================================
```

###### **2.操作系统**

```
抽象对象：进程 / 线程 / 资源
操作集合：创建 / 调度 / 同步 / 回收
实现层：PCB / 调度算法 / 信号量
```

###### **3.计算机组成及原理**

```
抽象对象：指令 / 寄存器 / 存储层次
操作集合：取指 / 执行 / 访存
实现层：硬件结构 / 时序
```

###### **4.计算机网络**

```
抽象对象：报文 / 连接 / 协议层
操作集合：建立 / 传输 / 释放
实现层：协议细节 / 状态机
```

## 2.抽成公共模板的条件

(1):至少被3道以上题目复用

(2):接口已经稳定(接口名称稳定)

(3):结构定义+操作实现已完成学习

避免给自己挖坑:ADT操作是否完整/操作语义是否清晰/写得出来、改得动、想得明白

## 3.数据结构中的ADT

**1.线性表**

```
InitList(L)
DestroyList(L)
ClearList(L)
ListEmpty(L)
ListLength(L)
GetElem(L, i)
LocateElem(L, x)
PriorElem(L, cur)
NextElem(L, cur)
ListInsert(L, i, x)
ListDelete(L, i)
TraverseList(L)
(存储结构差异:顺序表和链表)
```

**2.栈(Stack)**

```
InitStack(S)
DestroyStack(S)
StackEmpty(S)
Push(S, x)
Pop(S)
GetTop(S)
StackLength(S)
(栈没有遍历)
```

**3. 队列(Queue)**

```
InitQueue(Q)
DestroyQueue(Q)
QueueEmpty(Q)
EnQueue(Q, x)
DeQueue(Q)
GetHead(Q)
QueueLength(Q)
(实现问题:循环队列/链队)
```

**4.数组(Array/Vector)**

```
InitArray(A, dims)
DestroyArray(A)
Assign(A, indices, value)
Value(A, indices)
(实现问题:数组是映射关系,不是专门的ADT)
```

**5. 串(String)**

```
StrAssign(S, chars)
StrCopy(T, S)
StrEmpty(S)
StrLength(S)
StrCompare(S, T)
Concat(T, S1, S2)
SubString(Sub, S, pos, len)
Index(S, T)
ClearString(S)
DestroyString(S)
(KMP 是 Index 的高效实现)
```

**6.树**

```
InitTree(T)
DestroyTree(T)
TreeEmpty(T)
Root(T)
Parent(T, x)
FirstChild(T, x)
NextSibling(T, x)
InsertChild(T, p, i, c)
DeleteChild(T, p, i)
TraverseTree(T)
树是(层次结构 ADT)
```

**7.二叉树**

```
InitBiTree(T)
DestroyBiTree(T)
BiTreeEmpty(T)
CreateBiTree(T)
InsertChild(T, p, LR, c)
DeleteChild(T, p, LR)
PreOrderTraverse(T)
InOrderTraverse(T)
PostOrderTraverse(T)
LevelOrderTraverse(T)
二叉树 ≠ 树的特例(操作集合不同)
```

**8.图**

```
InitGraph(G)
DestroyGraph(G)
LocateVex(G, v)
GetVex(G, v)
PutVex(G, v, value)
FirstAdjVex(G, v)
NextAdjVex(G, v, w)
InsertVex(G, v)
DeleteVex(G, v)
InsertArc(G, v, w)
DeleteArc(G, v, w)
DFSTraverse(G)
BFSTraverse(G)
DFS/BFS 属于 ADT 操作
```

**9.哈希表**

```
InitHashTable(H)
DestroyHashTable(H)
Hash(key)
Insert(H, key)
Search(H, key)
Delete(H, key)
冲突处理是 实现层
```

**10.高级树**

````
1.并查集(Disjoint Set)
MakeSet(x)
Find(x)
Union(x, y)

2.AVL 树
Insert(T, x)
Delete(T, x)
Search(T, x)
LeftRotate(T)
RightRotate(T)
````

**11.高级图**

```
Prim(G)
Kruskal(G)
Dijkstra(G, v)
Floyd(G)
TopologicalSort(G)
CriticalPath(G)
算法本身就是 ADT 操作的“高阶实现”
```

