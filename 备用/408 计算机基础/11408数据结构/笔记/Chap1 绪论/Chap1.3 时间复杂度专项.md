# Chap1.3 时间复杂度专项

## 1.时间复杂度题目

**<font color=red>主要是别把2n和n\*\*2搞混了,同时n/2的迭代深度要控制住($log_2(n)$)</font>**

>   ==外层执行n/2,内层执行(1+n)n/2,整体O(n^2)==
>
>   除以2不是减少一半的工作量,而是(递归/循环深度)+1(乘以/除以2->都在攒2)

###### **<font color=red>1.下列算法的时间复杂度为?</font>**

```c
void fun(int n){
    int i=1;
    while(i<=n)
        i=i*2; // i,2i,4i,8i
}

```

>错误的:$O(n)$,while语句执行次数每次都折半,而不是开方
>
>**正确的:一直在攒2,所以应该是$log_2(n)$**
>
>只要循环变量是乘2/除2级别,不管边界是n或2n或n/2或n±100，都只影响常数项。
>
>注(1):while(i<=n) i=i*2;  $2^k = n\rightarrow log_2(n)$			$O(log_2n)$
>
>注(2):while(i<=n\*2) i=i*2; $2^k = 2n\rightarrow log_2(2n) = log_2(n)+1$ 	$O(log_2n)$
>
>注(3):while(i*2<=n) i=i\*2; $2^k >\frac{n}{2}\rightarrow k> log_2n-1$ 		$O(log_2n)$

###### **2.下列算法的时间复杂度为?**

```c
void fun(int n){
    int i=0;
    while(i*i*i<=n)
        i++;
}
```

>   while语句执行次数每次都开三次方

###### **3.求最后一行语句的频率最坏情况是</font>**

```c
for(i=n-1;i>1;i--)
    for(j=1;j<i;j++)
        if(A[j]>A[j+1])
            swap(A[j],A[j+1])
            // 10 9 8 7 6 5 4 3 2 1
```

>   最坏情况就是两个for执行完,外层for执行n次,内层for执行$n(n+1)/2\rightarrow [n^2(n+1)/2] \rightarrow O(n^2)$

###### **4.下列算法的时间复杂度为?**

```c
if(n>=0){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            printf("输入数据大于或等于0\n")
}
else{
	for(int j=0;j<n;j++)
        printf("输入数据小于零\n")
}
```

>   考虑最坏时间复杂度:条件一结果为O(n^2^)

###### **5.最后一句`m++;`的执行次数为?**

```c
int m=0,i,j;
for(i=1;i<=n;i++)
    for(j=1;j<=2*i;j++)
        m++;
```

>   外层for循环执行n次,内层for循环执行(2+2n)n/2 = n(n+1)次

###### **<font color=red>6.下列算法的时间复杂度为?</font>**

```c
int Func(int n){
    if(n==1)return 1;
    else return 2*Func(n/2)+n
}
```

>   错误的:每次n都除以2,所以是O(n)
>
>   正确的:递推式

###### **<font color=red>7.设n是描述问题规模的非负整数,下列程序的时间复杂度为?</font>**

```c
x = 2;
while(x<n/2)
    x = 2*x
```

>   错误的:while执行n/2->x会进一步缩小差距为n/4->O(n)
>
>   正确的:还是在攒2

###### **8.求整数n(n大于等于0)的阶乘算法如下,其时间复杂度为?**

```c
int fact(int n){
    if(n<=1)return 1;
    return n*fact(n-1):
}
```

>   实际上只是传递了n-1->O(n)

###### **<font color=red>9.下列程序段的时间复杂度是</font>**

```c
count = 0;
for(k=1;k<=n;k*=2)
    for(j=1;j<=n;j++)
        count++;
```

>   错误的:外层for执行n/2次,内层for执行n次->O(n^2)
>
>   正确的:外层执行$log_2(n)$次,内层执行n次->$O(nlog_2(n))$

###### **10.下列函数的时间复杂度为**

```c
int func(int n){
    int i=0,sum=0;
    while(sum<n)
        i = i+1;
        sum += i;
        // sum += ++i;
    return i;
}
```

>   设要执行c次,所以(1+(1+C))C/2 = n,所以$(2+C)C = 2n$,$$C = \sqrt{n}\rightarrow O(\sqrt{N})$$

###### **11.设n是描述问题规模的非负整数,下列程序段的时间复杂度为**

```c
x=0;
while(n>=(x+1)*(x+1))
    x=x+1
```

>   执行$\sqrt{n}$次,$\rightarrow O(\sqrt{n})$

###### **<font color=red>12.下列程序段的时间复杂度为</font>**

```c
int sum=0;
for(int i=1;i<n;i*=2)
    for(int j=0;j<i;j++)
        sum++;
```

>   错误的:外层执行n/2,内层执行(1+n)n/2,整体O(n^2)
>
>   正确的:外层执行1次的时候(外面一共是$log_2(n)-1$),内层执行i次->整体:$\sum^{log_2(n)-1}_{k=0}2^k$
>
>   (带入最后一位:$2^{log_2(n)}-1 = n-1\rightarrow O(n)$)

###### **13.下列程序段的时间复杂度为**

```c
int count=0,i,j;
for(i=1;i*i<=n;i++)
    for(j=1;j<=i;j++)
        count++;
```

>   外层执行$\sqrt{n}$,内层执行$\sqrt{n}$,整体O(n)

## 2.解答题

求解斐波那契数列,使用递归算法和非递归算法

```math
F(n) = 
\begin{cases}
0,&n=0\\
1,&n=1\\
F(n-1)+F(n-2),&n>1
\end{cases}
```

```C++
// 非迭代法
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int i = 0;
    int j = 1;
    int n = 10;
    vector<int> Fibonacci;
    Fibonacci.push_back(i);
    Fibonacci.push_back(j);
    for (int k = 0; k < n; k++) {
        Fibonacci.push_back(Fibonacci[k]+Fibonacci[k+1]);
    }
    for (int num:Fibonacci) {
        cout << num << " ";
    }
    return 0;
}
```

```C++
#include<iostream>
#include<vector>
using namespace std;
int Fib(int n){
    if(n==1 || n==2){
        return 1;
    }else{
        return Fib(n-2)+Fib(n-1)
    }
}
int main(){
	cout<< Fib(n)<< endl;
}
```

