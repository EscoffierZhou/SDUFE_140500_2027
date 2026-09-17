# Chap6.3 图的遍历

图的遍历:从图中的某一个顶点触发,按照某种搜索策略,沿着图中的边访问所有顶点,并且每个顶点仅被访问一次

>   **额外注意的是:需要记录已访问的结点,需要设置一个visited[]数组**

## 1.广度优先搜索BFS(Queue)

###### **1.BFS主要思想:和树的层次遍历完全一致**

>   从一个起始顶点v出发,依次访问v的所有未被访问过的邻接结点$w_1,w_2,\cdots,w_i$
>
>   然后邻接结点作为起始结点,依次访问w的所有未被访问过的邻接结点$w_j,w_k,\cdots$

Dijkstra单源最短路径算法和Prim生成树算法使用了BFS类似的思想

**BFS基本上没有回溯实现方式:因为遍历完了一层就直接下一层了,而不会再回溯已访问结点**

```C++
bool visited[MAX_VERTEX_NUM];
void BFSTraverse(Graph G){
    Queue Q;
    for(i=0;i<G;++i)		
        visited[i]=FALSE;	// 访问数组初始化
    InitQueue(Q);			// 初始化辅助队列Q
    for(i=0;i<G.vexnum;++i)
        if(!visited)
            BFS(G,i);		
}
// =========================(邻接表法)=================================
/*ALGraph{
	int vexnum,arcnum,
	[
	vertices[0]:(VNode:data,ArcNode1.[adjvex|next]-ArcNode2.[adjvex|next])
	vertices[1]:(VNode:data,ArcNode3.[adjvex|next]-ArcNode4.[adjvex|next])
	...
	]
}*/
void BFS_Adjacency_list(Graph G, int v) {
    // 1. 起点初始化
    visit(v);				// 访问初始结点
    visited[v] = true; 		// 访问初始结点,标记为true
    Enqueue(Q, v); 			// 起点入队
    while (!IsEmpty(Q)) {
        Dequeue(Q, v); 		// 弹出一个点当雷达中心
        for (ArcNode *p = G.vertices[v].firstarc; 
             // 从 v 出发的所有边的链表入口
             p != NULL; 
             p = p->nextarc) {
            int w = p->adjvex;		// 邻接顶点的下标
            if (!visited[w]) {
                visit(w);			// w为未访问的邻接点
                visited[w] = true; // 必须在入队之前打标
                Enqueue(Q, w);		
            }
        }
    }
}
// =========================(邻接矩阵法)===============================
/*typedef struct {
   char vex[MAX_VERTEX_NUM];                  // 顶点数组(存名字)
   int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵 
   int vexnum, arcnum;                        // 当前顶点数和边数
} MGraph;*/
void BFS_Adjacency_Matrix(Graph G, int v) {
    // 1. 起点初始化
    visit(v);				// 访问初始结点
    visited[v] = true; 		// 访问初始结点,标记为true
    Enqueue(Q, v); 			// 起点入队
    while (!IsEmpty(Q)) {
        Dequeue(Q, v); 		// 弹出一个点当雷达中心
        for(w=0;w<G.vexnum;w++)
            if(visited[w]==FALSE && G.edge[v][w]==1){
                visit(w);			// w为未访问的邻接点
                visited[w] = true; // 必须在入队之前打标
                Enqueue(Q, w);	
            }
    }
} 
```

###### **2.性能分析**

BFS需要借助一个辅助队列Q进行逐层访问,所以最坏空间复杂度情况是O(|V|)

时间复杂度(1):邻接矩阵:查找邻接点			   -> O(|V|^2^)

时间复杂度(2):邻接表  :顶点入队O(|V|),通过边搜索邻接点O(|E|) -> O(|V|+|E|)

###### **3.BFS求单源最短路径问题**

最短路径:所有从顶点u到顶点v的路径中所含边数的最小值

**使用BFS的原因:BFS总之从最近的点开始遍历**

```C++
#define infty 10000
// 只是多了一个记录数组
void BFS_MIN_Distance(Graph G,int u){
    for(i=0;i<G.vexnum;++i)
        d[i] = infty;	 		// Extra
    visited[u]=TRUE;d[u]=0;
    EnQueue(Q,u);
    While(!QueueEmpty(Q)){
        DeQueue(Q,u);
        for(w=FirstNeighbor(G,u);
            w>=0; // 顶点结点可以是0
            w=NextNeighbor(G,u,w))
            if(!visited[w]){
                visited[w]=TRUE;
                d[w]=d[u]+1;	// Extra:按层次+1
                EnQueue(Q,w);
            }
    }
}
```

###### **4.BFS广度优先生成树**

在BFS的过程中,所经过的边与访问的顶点共同构成一颗树

**<font color=red>额外的,只有图是连通的,最后才会生成一颗覆盖所有结点的生成树</font>**

>   生成树:包含所有顶点+无环+连通

**如果采用邻接矩阵存储:则树是唯一的(for循环从0到n,固定)**

**如果采用邻接表存储:则树是不唯一的(A->ArcNode的插入顺序不唯一,不唯一)**

>   **<font color=red>如果已经给了固定的邻接表,其对应的BFS广度优先搜索树的访问顺序是固定的</font>**

## 2.深度优先搜索DFS(Stack)

###### **1.DFS基本思想**

首先访问图的一个起始顶点v,然后从v出发,访问v的一个未访问邻接顶点$w_1$

>   **<font color=red>当无法继续向下访问的时候,回退至上一顶点(递归返回)</font>**

```C++
bool visited[MAX_VERTEX_NUM];
void DFSTraverse(Graph G){
	for(i=0;i<G.vexnum;i++)// 初始化
        visited[i]=FALSE;
    for(i=0;i<G.vexnum;i++)
        if(!visited[i])
            DFS(G,i);
}
// =========================(邻接表法)=================================
/*ALGraph{
	int vexnum,arcnum,
	[
	vertices[0]:(VNode:data,ArcNode1.[adjvex|next]-ArcNode2.[adjvex|next])
	vertices[1]:(VNode:data,ArcNode3.[adjvex|next]-ArcNode4.[adjvex|next])
	...
	]
}*/
void BFS_Adjacency_list(Graph G, int v) {
    // 1. 起点初始化
    visit(v);				// 访问初始结点
    visited[v] = true; 		// 访问初始结点,标记为true
    Enqueue(Q, v); 			// 起点入队
    while (!IsEmpty(Q)) {
        Dequeue(Q, v); 		// 弹出一个点当雷达中心
        for (ArcNode *p = G.vertices[v].firstarc; 
             p != NULL; 
             p = p->nextarc) {
            int w = p->adjvex;		// 邻接顶点的下标
            if (!visited[w]) {
                visit(w);			// w为未访问的邻接点
                visited[w] = true; // 必须在入队之前打标
                Enqueue(Q, w);		
            }
        }
    }
}
void DFS_Adjacency_list(ALGraph G,int i){
    visit(i); 			// 访问初始结点
    visit[i]=TRUE;
    for (ArcNode *p = G.vertices[i].firstarc; 
             p != NULL; 
             p = p->nextarc) {
        j = p->adjvex;
        if(visited[j]==FALSE)
            DFS(G,j);
    }
}

// =========================(邻接矩阵法)===============================
/*typedef struct {
   char vex[MAX_VERTEX_NUM];                  // 顶点数组(存名字)
   int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵 
   int vexnum, arcnum;                        // 当前顶点数和边数
} MGraph;*/
void BFS_Adjacency_Matrix(Graph G, int v) {
    // 1. 起点初始化
    visit(v);				// 访问初始结点
    visited[v] = true; 		// 访问初始结点,标记为true
    Enqueue(Q, v); 			// 起点入队
    while (!IsEmpty(Q)) {
        Dequeue(Q, v); 		// 弹出一个点当雷达中心
        for(w=0;w<G.vexnum;w++)
            if(visited[w]==FALSE && G.edge[v][w]==1){
                visit(w);			// w为未访问的邻接点
                visited[w] = true; // 必须在入队之前打标
                Enqueue(Q, w);	
            }
    }
} 
void DFS_Adjacency_Matrix(ALGraph G,int i){
    visit(i);
    visit[i]=TRUE;
    for(j=0;j<G.vexnum;j++){
        if(visited[j]==FALSE &&G.edge[i][j]==1)
            DFS(G,j);
    }
}
```

仍然:如果是邻接矩阵生成的BFS/DFS都是唯一的,如果是邻接表则都不唯一

###### **2.性能分析**

DFS需要借助一个系统栈(或辅助栈S)进行逐层访问,所以最坏情况是O(|V|)

时间复杂度(1):邻接矩阵:查找邻接点			   -> O(|V|^2^)

时间复杂度(2):邻接表  :顶点入队O(|V|),通过边搜索邻接点O(|E|) -> O(|V|+|E|)

###### **3.深度优先的生成树和生成森林**

在DFS的过程中,所经过的边与访问的顶点共同构成一颗树

**<font color=red>额外的,只有图是连通的,最后才会生成一颗覆盖所有结点的生成树</font>**

>生成树:包含所有顶点+无环+连通

**如果采用邻接矩阵存储:则树是唯一的(for循环从0到n,固定)**

**如果采用邻接表存储:则树是不唯一的(A->ArcNode的插入顺序不唯一,不唯一)**

>   **<font color=red>如果已经给了固定的邻接表,其对应的DFS广度优先搜索树的访问顺序是固定的</font>**

## 3.图的遍历和图的连通性

**==图的遍历算法可以用于判断图的连通性==**

操作:在BFS/DFS外面套一层for循环->调用的次数就是连通分量的个数

```C++
for (int i = 0; i < G.vexnum; i++) {
    // 一旦某个点被访问过，就属于某个连通分量，不再重复搜索
    if (!visited[i]) {  // 只对没有访问过的结点做Traverse
        BFS(G, i);  	// 从这个点出发遍历一整块连通分量
        count++;    	// 连通分量 +1
    }
}
```

**有向图单次调用BFS/DFS不一定能访问到该子图的所有结点**

>   0 → 1 → 2 → 3,其实并非连通,因为3到不了0

```
6
62
62(1)(5)
62(1(3)(4))(5)
62(1(3(7))4((8)(9))(5)
621534789
```

```
6
62
621349867
```



