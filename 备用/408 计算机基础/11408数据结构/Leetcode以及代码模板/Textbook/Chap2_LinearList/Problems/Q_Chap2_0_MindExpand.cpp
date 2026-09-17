#include <iostream>
#define MAXSIZE 50
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// === 2. 核心算法: 快速排序 (O(NlogN)) ===
// 考研标准写法: 这里的 Partition 逻辑是最经典的
int Partition(int A[], int low, int high) {
    int pivot = A[low]; // 选取第一个元素作为枢轴
    while (low < high) {
        // 从右向左找比 pivot 小的
        while (low < high && A[high] >= pivot)
            high--;
        A[low] = A[high]; // 移到左边
        // 从左向右找比 pivot 大的
        while (low < high && A[low] <= pivot)
            low++;
        A[high] = A[low]; // 移到右边
    }
    A[low] = pivot; // 枢轴归位
    return low;     // 返回枢轴位置
}

void QuickSort(int A[], int low, int high) {
    if (low < high) {
        int pivotPos = Partition(A, low, high);
        QuickSort(A, low, pivotPos - 1);  // 递归左半边
        QuickSort(A, pivotPos + 1, high); // 递归右半边
    }
}

// === 3. 核心算法: 双指针查找 (O(N)) ===
// 查找和为 x 的所有对
void FindPairs(int A[], int n, int x) {
    int i = 0;          // 左指针 (Low)
    int j = n - 1;      // 右指针 (High)
    bool found = false;
    cout << "满足条件的整数对为: " << endl;
    while (i < j) {
        int sum = A[i] + A[j];
        if (sum == x) {
            cout << "(" << A[i] << ", " << A[j] << ")" << endl;
            found = true;
            // 找到一对后，继续寻找可能的下一对
            // 注意: 如果数组可能有重复元素，这里需要特殊处理去重
            // 考研基础题通常可以直接移动两个指针
            i++;
            j--;
        } else if (sum < x) {
            // 和太小，说明左边的数太小了，左指针右移
            i++;
        } else {
            // 和太大，说明右边的数太大了，右指针左移
            j--;
        }
    }
    if (!found) cout << "未找到满足条件的整数对。" << endl;
}

// === 4. 主函数: 鲁棒的输入处理 ===
int main() {
    int A[MAXSIZE];
    int n = 0;
    int x;

    // 模拟考研机试输入:
    // 通常格式是: 先输入数组长度 n，再输入 n 个数，最后输入目标值 x
    // 或者: 直接输入一串数字
    // 既然你想用 "以 e 结尾" 或类似非数字结尾，利用 cin 的特性：
    // cin 读到非整型字符（如 'e'）会进入 fail 状态，停止读取

    cout << "请输入数组元素(直接输入整数，输入非数字字符结束): " << endl;
    int val;
    // 只要输入的是整数，循环就继续；遇到 'e' 或其他字符，循环终止
    while (n < MAXSIZE && cin >> val) {
        A[n++] = val;
    }
    // 清除 cin 的错误标志，以便后续还能读取 x (如果输入流被 'e' 卡住的话)
    cin.clear();
    cin.ignore();
    cout << "请输入目标和x: ";
    cin >> x;
    QuickSort(A, 0, n - 1);
    cout << "排序后的数组: ";
    for(int k=0; k<n; k++) cout << A[k] << " ";
    cout << endl;
    FindPairs(A, n, x);
    return 0;
}