#include <iostream>
#include <vector>
using namespace std;

// int Calculate(int n) {
//     if (n == 1 || n == 2) {
//         return 1;
//     }
//     return Calculate(n - 1) + Calculate(n - 2);
// }
// 记忆化+递归=有点DP的味道了

int Calculate(vector<int>& fib, int n) {
    // 1.递归调用树会重复计算,如果值不为-1就可以不算了
    if (fib[n] != -1) return fib[n];
    // 2.最小子问题
    if (n <= 2) return 1;
    // 3.递归关系是
    fib[n] = Calculate(fib, n - 1) + Calculate(fib, n - 2);
    return fib[n];
}
int main() {
    int n = 10;
    vector<int> fib(n + 1, -1); // 这里额外初始化为-1
    cout << Calculate(fib,n) << endl;
    return 0;
}
