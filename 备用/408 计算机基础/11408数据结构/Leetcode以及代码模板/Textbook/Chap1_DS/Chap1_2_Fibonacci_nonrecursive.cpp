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

