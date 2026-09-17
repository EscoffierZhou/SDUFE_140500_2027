// 数学理论:
// F(2k)   = F(k) * [2F(k+1) − F(k)]
// F(2k+1) = F(k+1)² + F(k)²
#include<stdlib.h>
#include<iostream>
#include<vector>
using namespace std;

pair<long long, long long> fib_pair(long long n) {
    if (n == 0)
        return {0, 1};
    auto [a, b] = fib_pair(n / 2); // a = F(k), b = F(k+1)
    long long c = a * (2 * b - a); // F(2k)
    long long d = a * a + b * b;   // F(2k+1)
    if (n % 2 == 0)
        return {c, d};
    else
        return {d, c + d};
}
long long fib(long long n) {
    return fib_pair(n).first;
}
int main() {
    int n = 10;
    auto result = fib_pair(n);

    // 只能输出单个结果
    // pair<long long,long long>需要结构化绑定
    cout<<result.first<< endl;
    cout<<result.second<< endl;
    //或者 auto[f_n,f_n1] = fib_pair(n)

    // 迭代需要更换对象
    // auto p = fib_pair(n);
    // vector<long long> v = {p.first, p.second};
    // for (auto x : v) cout << x << endl;
    return 0;
}