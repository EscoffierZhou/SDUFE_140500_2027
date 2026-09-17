#include<iostream>
#include<algorithm>
using namespace std;
// 总结(1):是否使用dummy?是否参与运算?
//        dummy头节点不参与运算(没有值),所以需要缓存dummy->next
// 总结(2):while 条件是否是 p != nullptr？
//        while条件别写反了
// 总结(3):new 的节点next是否置空nullptr？
//        别忘了推进指针
// 总结(4):初始化链表和推进节点的三件套写法是否正确?
//        (新建节点,开始)ListNode * List1 = new ListNode();
//        (置空next指针)List1->next = nullptr;
//        (新建操作指针)ListNode* cur1 = List1;
//        (新建节点,后序)cur1->next = new ListNode();


// 必死条件(1):(main中)头节点参与运算
// 必死条件(2):(main中)next指针没有推进/没有使用循环
// 必死条件(3):(构造中)新节点没有初始化next指针,node->next = nullptr;
// 必死条件(4):(main中)用值判断阶段是否存在->用node != nullptr)判断
// 语法错误(1):(main中)vector的初始化/vector的容量


struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    ListNode* new_List = new ListNode();   // 新链表初始化写法
    new_List->next = nullptr;
    ListNode* cur = new_List;              // 指针初始化写法
    int carry = 0;
    while (l1 || l2 || carry) {
        int x = l1 ? l1->val : 0;
        int y = l2 ? l2->val : 0;
        int sum = x + y + carry;
        carry = sum / 10;
        cur->next = new ListNode();
        cur->next->val = sum % 10;
        cur->next->next = nullptr;
        cur = cur->next;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    return new_List->next; // 第一个节点不存储数据
}
int main() {
    // 不建议使用auto:std::initializer_list<int>
    int a[] = {9,9,9};
    int b[] = {9,9,9,9,9};
    ListNode * List1 = new ListNode();
    List1->next = nullptr;
    ListNode* cur1 = List1;
    for (int num:a) {
        cur1->next = new ListNode();
        cur1->next->val = num;
        // 后继必须要写上nullptr,否则next变成野指针
        cur1->next->next = nullptr;
        cur1 = cur1->next;
    }
    ListNode * List2 = new ListNode();
    List2->next = nullptr;
    ListNode* cur2 = List2;
    for (int num : b) {
        cur2->next = new ListNode();
        cur2->next->val = num;
        cur2->next->next = nullptr;
        cur2 = cur2->next;
    }
    // 注意这里要传入next不然都是0
    // 不用auto,而是ListNode*

    ListNode* result = addTwoNumbers(List1->next,List2->next);
    ListNode* ptr = result;
    while (ptr != nullptr) {
        cout << ptr->val << " ";
        ptr = ptr->next;
    }
    cout << endl;
    return 0;
}