# Chap4.2 串的模式匹配

## 1.简单的模式匹配算法

**基本思路:暴力,主串S和模式串T,从主串S的第一个字符开始与模式串T的首字符比较**

>   如果存在都相等,则继续比较后续字符
>
>   如果存在不相等,则主串S的指针移动到下一位,重新从T的首字符开始比较

## 2.串的模式匹配算法(KMP)

###### **1.KMP算法的基本术语**

**问题：传统的模式匹配算法(naive)最坏情况是``O(mn)``**:`S:aaaaaab`,`T:ab`

**(对于字符串:`abcdabc`)**

**KMP算法术语(1):前缀:`a`,`ab`,`abc`,`abcd`,`abcda`,`abcdab`	<font color=red>(不包含abcdabc)</font>**

**KMP算法术语(2):后缀:`c`,`bc`,`abc`,`dabc`,`cdabc`,`bcdabc`	<font color=red>(不包含abcdabc)</font>**

**KMP算法术语(2):(部分匹配值)最长相等前后缀值LPS:**

```
		前缀内容							后缀内容							最长前后缀长度
a		\empty								\empty									0
ab		{a}									{b}										0
abc		{a,ab}								{c,bc}									0
abcd	{a,ab,abc}							{d,cd,bcd}								0
abcda   {a,ab,abc,abcd}						{a,da,cda,bcda}							a的长度是1			
abcdab	{a,ab,abc,abcd,abcda}				{b,ab,dab,cdab,bcdab}					ab的长度是2
abcdabc {a,ab,abc,abcd,abcda,abcdab}		{c,bc,abc,dabc,cdabc,bcdabc}			abc的长度是3
```

**KMP算法术语(3):PM数组:由最长相等<font color=red>真(前后缀长度必须小于模式串长度)</font>后缀长度组成的下标==从0开始的数组==**

```
abcdabc: 0000123
```

###### **2.PM表的建立(应用层:最长相等前后缀,人类专用)**

快速写法PM table(索引表):状态机

**<font color=red>需要注意的是:j虽然也有查询,但是这个查询的过程是常数(甚至可以数)</font>**

**(1)建立PM表**

**<font color=deeppink>状态机操作(1):如果P[i]==P[j]	i++,PM[i]=j,j++</font>**

**<font color=deeppink>状态机操作(2):如果P[i]!=P[j]	i++,while(j=PM[j-1]){直到回退到0},其中跳转中没找到相同的字符,PM[i]=0</font>**

**<font color=deeppink>状态机操作(3):如果P[i]!=P[j]	i++,while(j=PM[j-1]){直到回退到0},其中跳到j=u处找到了相同的字符,PM[i]=u+1</font>**

**<font color=deeppink>状态机操作(4):匹配过程中,匹配串向后移动位数    = 已匹配的字符数p - 对应部分匹配值PM[p-1]</font>**

**<font color=red>特点:模式串的下标为0,无论如何i都向前,在期间的跳转操作被视为内部操作</font>**

```
Step(1):建立PM表
状态机操作(1):如果P[i]==P[j],PM[i]=j,				  j指针:j++
(状态机操作(2):如果P[i]!=P[j],PM[i]=(需要比较j=PM[j-1],存在相同+1,不存在.到头则为0,j指针:PM[j-1],i前进)

=====================================================================
PM:		0 	1	2	3	4	5	6	7
ptr:	0	1	2	3	4	5	6	7
P:		a 	b 	a 	c 	a 	b 	a 	b		
=====================================================================						
时刻T	  当前指针状态					   (比较)    PM表操作	        指针操作(效果在下一刻体现)
(T=0)   j	i							 初始化	PM[0]=0	
(T=1)	j	i							 不等		 j=PM[0-1]<[0],不存在   i前进
												   PM[1]=0
(T=2)	j   	i  					     相等      PM[2]=1     		 i,j前进	
(T=3)		j    	 i					 不等      j=PM[1-1]=P[0]=0    回退到j=0(a和c不等)
												   j=PM[0-1]<[0],不存在
												   PM[3]=0			  i前进
(T=4)   j				i				 相等		 PM[4]=1	 		 i,j前进	
(T=5)   	j				i			 相等		 PM[5]=2	 		 i,j前进	
(T=6)			j				i        相等		 PM[6]=3	 		 i,j前进	
(T=7)				j				i    不等		 j=PM[3-1]=PM[2]=1	 回退到j=1(b和b相同)		!!!状态机(3)
												   PM[7]=1+1=2
=====================================================================	
Step(2):通过PM表进行匹配
状态机(3):移动位数=已匹配的字符数p - 对应部分匹配值PM[p-1]
Index_P:0	1	2	3	4	5	6	7
P:		a 	b 	a 	c 	a 	b 	a 	b
PM		0	0	1	0	1	2	3	2
=====================================================================
Index_S:0	1	2	3	4	5	6	7	8	9	10	11	12	13	14
S: 		a 	b 	a 	c 	a 	b 	a 	a 	b 	a 	c 	a 	b 	a 	b
		|	|	|	|	|	|	|	|!								(前面经过了6个while)
		a 	b 	a 	c 	a 	b 	a 	b!   							S[7]失配;已匹配7;PM[7-1]=PM[6]=3;7-3=4
					->	a 	b 	a 	c!	a	b	a	b				S[7]失配;已匹配3;PM[3-1]=PM[2]=1;3-1=2						 	 	 a	 b!  a	 c	 a	 b	 a	 b		 S[7]失配;已匹配1:PM[1-1]=PM[0]=0;i,j共同
									a	b   a	c	a	b	a	b   S[7]成功;单次while循环结束,ij指针遍历,成功
```

```
Eg(1):
状态机操作(1):如果P[i]==P[j],PM[i]=j,				  j指针:j++
状态机操作(2):如果P[i]!=P[j],PM[i]=(需要比较j=PM[j-1],存在相同+1,不存在.到头则为0,j指针:PM[j-1],i前进
=====================================================================
PM:		0 	1	2	3	4	5	
ptr:	0	1	2	3	4	5
P:		a 	b 	a 	b 	a 	c
=====================================================================
时刻T	  当前指针状态					   (比较)    PM表操作	        指针操作(效果在下一刻体现)
(T=0)	j	i							 初始化	PM[0]=0				
(T=1)	j	i							 不等		 j=PM[j-1]~0(到头)  i前进
												   PM[1]=0
(T=2)	j		i						 相等		 PM[2]=1			i,j前进
(T=3)   	j		i					 相等		 PM[3]=2			i,j前进
(T=4)			j		i				 相等		 PM[4]=3			i,j前进
(T=5)				j		i			 不等		 j=PM[j-1]=P[2]=1	回退到j=1(c和b不等)
			j				i					   j=PM[j-1]=PM[0]=0  回退到j=0(c和a不等)
		j					i					   PM[5]=0	 		  i=S.length()终止
=====================================================================
PM:		0	0	1	2	3	0
```

```
(其它练习)
P1:		abcdabeabf
        0000120120
P2:		abcdeabfabc
		00000120123
P3:		aabcadaabe
		0100101200
P4:		aaaabaacda
		0123012001
```

**<font color=red>KMP的核心价值:指导模式串在失配后的右滑距离,主串指针始终没有回溯O(m+n)</font>**

>   **若匹配序列中不存在相同的前后缀(PM值为0),则滑动位数最大:模式串首字符在失配处(注意一个while循环里面)**
>
>   **若存在最长相等前后缀(PM值存在),则模式串向右滑倒和主串相同后缀的位置,跳过已知部分,避免重复比较**
>
>   当然如果第一个字符就失配,则已匹配字符数为0,模式串整体右移一位,并且从下一位S匹配
>
>   **<font color=red>综上:模式串右滑均为"已匹配字符数-对应部分匹配值"</font>**

###### **3.next数组(CPU寄存器层面的优化,计算机专用)**

KMP算法的核心特性:每趟匹配失败的时候,主串指针i不回溯,仅模式串指针j调整

>   因此next数组:next[j]的含义是:当模式串第j个字符失配时,下一轮应该从模式串的第next[j]个位置继续与主串当前字符比较
>
>   **<font color=red>作用上和PM表完全相同</font>,但是为了避免减法ALU开销而做出的优化->实际上并不会生成PM表,而是直接生成next数组**

**(1)PM表转换为next数组**

得到了PM表以后仅需要简单操作即可得到next数组:`next[j] = PM[j-1] + 1`

比如`abacabab`得到了PM表:`00101232`

```
(1)整体右移:抄表
	_	0	0	1	0	1	2	3
(2)整体加1:因为数组下标从1开始
	_	1	1	2	1	2	3	4
(3)首位补0
	0	1	1	2	1	2	3	4
```

**(2)直接建立next数组(首先花O(m)的时间单独构建next数组)**

```C++
void get_next(SString T,int next[]){
    int i=1;
    int j=0;
    next[1]=0;	// 初始化(底线):第一个字符失配,主串指针前进
    while(i< T.length){
        if(j==0 || T.ch[i] == T.ch[j]){	
            // j==0:如果当前字符没有匹配的前缀,只能从头开始
            // T.ch[i] == T.ch[j]:匹配成功,前后缀长度增加
            ++i;++j;
            next[i] = j;	// 记录下一位的next值
        }else{
        	j=next[j];		// 失配了,j指针疯狂回退
        }
    }
}
```

**<font color=deeppink>状态机操作(1):如果j==0			       i和j一起向后移动,next[i]=j</font>**

**<font color=deeppink>状态机操作(2):如果j!=0,并且,ij指向的字符相同	   i和j一起向后移动,next[i]=j</font>**

**<font color=deeppink>状态机操作(3):如果j!=0,并且,ij指向的字符不同	   i不变,j回退,j=next[j]</font>**

**<font color=deeppink>状态机操作(4):在匹配中,j\==0,"或",S[i]==P[j]匹配成功    i++,j++	</font>**

**<font color=deeppink>状态机操作(5):在匹配中,j!=0,"且",S[i]!=P[j]匹配成功    i不变,j=next[j]</font>**

**<font color=red>特点:每次j跳转,极端情况下`aaaaab`会慢慢往前走,然后i一直没有反应</font>**

```
状态机操作(1):如果j==0							-> i和j一起向后移动,next[i]=j
状态机操作(2):如果j!=0,并且,ij指向的字符相同		 -> i和j一起向后移动,next[i]=j
状态机操作(3):如果j!=0,并且,ij指向的字符不同		 -> i不变,j回退,j=next[j]
状态机操作(4):在匹配中,j==0,"或",S[i]==P[j]匹配成功    i++,j++	
状态机操作(5):在匹配中,j!=0,"且",S[i]!=P[j]匹配成功    i不变,j=next[j]
(只要j没有回退到0,那么while循环会一直执行)
=====================================================================
Index_P:	1	2	3	4	5	6	7	8	<-	注意:模式串从1开始下标,方便描述
P:			a 	b 	a 	c 	a 	b 	a 	b						
next:	   (0)	[]	[]	[]	[]	[]	[]	[]	<-  初始化:i=1,j=0,next[1]=0
=====================================================================
(时刻)  (指针做法)								(描述)			(i,j指针移动后位置)	 (next数组操作)
T = 1:	j	i									j==0,ij后移	 	 i=2,j=1 		   		next[i]=next[2]=1
T = 2:		j	i								j!=0,ij不同,移动j  i=2,j=next[j]=next[1]=0 		-
		j	    i								j==0,ij后移		 i=3,j=1				next[i]=next[3]=1
T = 3:  	j		i							j!=0,ij相同,ij后移 i=4,j=2				  next[i]=next[4]=2
T = 4:  		j		i						j!=0,ij不同,移动j  i=4,j=next[j]=next[2]=1 				
			j			i						j!=0,ij不同,移动j  i=4,j=next[j]=next[1]=0
		j				i						j==0,ij后移		 i=5,j=1			    next[i]=next[5]=1
T = 5:		j				i					j!=0,ij相同,ij后移 i=6,j=2				  next[i]=next[6]=2
T = 6:			j				i				j!=0,ij相同,ij后移 i=7,j=3				  next[i]=next[7]=3
T = 7:				j				i			j!=0,ij相同,ij后移 i=8,j=4				  next[i]=next[8]=4
=====================================================================
next:	   (0)	1	1	2	1	2	3	4	
P:     		a  	b  	a  	c  	a  	b  	a  	b
Index:  	1  	2  	3  	4  	5  	6  	7  	8  	9  	10 	11
S:     		a  	b  	a  	c  	a  	b  	a  	a  	b  	a  	b   <-  初始化:!!!!!i=1,j=1!!!!!!!!!!!
(时刻)  (指针做法)										(描述)			(i,j指针移动后位置)	 
T=1			i,j											S[i]==P[j]			i=2,j=2
T=2				i,j										S[i]==P[j]			i=3,j=3
T=3					i,j									S[i]==P[j]			i=4,j=4
T=4						i,j								S[i]==P[j]			i=5,j=5
T=5							i,j							S[i]==P[j]			i=6,j=6
T=6								i,j						S[i]==P[j]			i=7,j=7
T=7									i,j					S[i]==P[j]			i=8,j=8
T=8										i,j				S[i]!=P[j]			i=8,j=next[8]=4
						j				i				S[i]!=P[j]			i=8,j=next[4]=2
				j						i				S[i]!=P[j]			i=8,j=next[2]=1
			j							i				S[i]==P[j]			i=9,j=2
T=9				j							i			S[i]==P[j]			i=10,j=3
T=10				j							i		S[i]==P[j]			i=11,j=4
T=11					j							i	S[i]!=P[j]			i=11,j=next[4]=2
				j									i	S[i]==P[j]			i=12,j=3(finished)
```

###### **4.next数组大招:全局视野识别**

```
第一剑： next[1] 永远无脑填 0					因为next[1-1]在第0位没有字符
第二剑： next[2] 永远无脑填 1					因为next[2-1]在第1位前后缀就是本身
第三剑:  next[j],只看前面j-1个字符组成的子串中,最长前后缀长度L,然后next[j]=L+1

!!!!!!!!!!!!!!!!要+1!!!!!!!!!!!
对于aaab,它的aaa前后缀长度是2而不是3

P:     		a  	b  	a  	c  	a  	b  	a  	b
Index:  	1  	2  	3  	4  	5  	6  	7  	8 
next数组			解释							最终数值
next[1]:		 第一剑							0
next[2]:		 第二剑							1
next[3]:		 ab(无相等前后缀=0)	  			  1
next[4]:		 aba(有相等前后缀=1)				  2
next[5]:		 abac(无相等前后缀=0)	 			  1
next[6]:		 abaca(有相等前后缀=1)			  2	
next[7]:		 abacab(有相等前后缀=2)		 	  3
next[8]:		 abacaba(有相等前后缀=3)			  4		
next数组:	  0	 1	1	2	1	2	3	4
```

###### **5.nextval数组**

**问题:next数组的回退机制很好,在P[j]处失配,回退到P[k],但是如果P[k]==P[j]不就白退了,连续撞车**

**<font color=red>注:必须先求出next数组,然后再转换为nextval数组</font>**

```
第一剑： nextval[1] 永远无脑填 0
第二剑:  对于后面每一个j,都要看它原本要退回的位置:
		如果P[j]!=P[k],不会连续撞墙,保持原判
		如果P[j]==P[k],导致连续撞墙,nextval[j]=nextval[k](继承,不需要while)
=====================================================================
P:     		a  	b  	a  	c  	a  	b  	a  	b
Index:  	1  	2  	3  	4  	5  	6  	7  	8 
next数组:	  0	  1	  1	  2	   1	2	3	4
=====================================================================
nextval数组			next数组			  解释						最终数值
nextval[1]:		     next[1]=0			第一剑						  nextval[1]=0
nextval[2]:		 	 next[2]=1			P[2](b)!=P[1](a)			nextval[2]=1	
nextval[3]:		 	 next[3]=1			P[3](a)==P[1](a)			nextval[3]=nextva[1]=0
nextval[4]:		 	 next[4]=2			P[4](c)!=P[2](b)			nextval[4]=2
nextval[5]:			 next[5]=1			P[5](a)==P[1](a)			nextval[5]=nextva[1]=0
nextval[6]:		     next[6]=2			P[6](b)==P[2](b)			nextval[6]=nextva[2]=1
nextval[7]:		 	 next[7]=3			P[7](a)==P[3](a)			nextval[7]=nextva[3]=0
nextval[8]:		 	 next[8]=4			P[8](b)!=P[4](c)			nextval[8]=4
nextval数组:0	 1	0	2	0	1	0	4
```

## 3.本章习题

CB(CD)DB CBCBC BA

CB(CD)DB CBCBC BA

注意next数组+1,以及遇到aaab的时候是真前后缀,aaa的前后缀长度为2
