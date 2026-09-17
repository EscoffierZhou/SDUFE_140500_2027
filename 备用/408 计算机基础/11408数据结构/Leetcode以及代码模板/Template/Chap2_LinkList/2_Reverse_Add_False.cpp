#include<vector>
#include <algorithm>
using namespace std;
// T(n) = O(n),S(n) = O(n)
// 单链表不能从后往前遍历 -> 转成数组/vector -> 对两个数组做加法 -> 再转回链表
// 致命错误(1):链表的遍历是使用while,而不是if(l1->next)
// 致命错误(2):vetor初始化,和vector的大小(size而不是length)
// 致命错误(3):加法不是二维问题,会导致重复加法
// 致命错误(4):最后还要倒腾成链表
struct ListNode {
    int val;
    ListNode * next;
};
struct ListNode* addTwoNumbers(const struct ListNode* l1,const struct ListNode* l2) {
    // 问题(1):单项链表无法从后遍历
    // 问题(2):想不到一个[]可以完成的
    vector<int>L1;
    vector<int>L2;
    int result,next;
    while(l1){
        L1.push_back(l1->val);
        l1 = l1->next;
    }
    while(l2){
        L2.push_back(l2->val);
        l2 = l2->next;
    }
    reverse(L1.begin(),L1.end());
    reverse(L2.begin(),L2.end());
    int longer_length = L1.size()>L2.size()?L1.size():L2.size();
    int shorter_length = L1.size()>L2.size()?L2.size():L1.size();
    vector<int> sum(longer_length + 1, 0);
    // 为了避免倒腾,写了两个情况
    // L1更长
    for(int i = 0;i<longer_length;i++){
        for(int j = 0;j<shorter_length;j++){
            if(longer_length == L2.size()){
                if(L2[j]){
                    // 单个Node.val范围是[0,9]
                    result = L1[i]+L2[j];
                    if(result < 10){
                        sum[i] = sum[i]+result;
                    }else{
                        sum[i] = sum[i]+(result%10);
                        next = i+1;
                        sum[next] = result / 10;
                    }
                }else{
                    sum[i] = L1[i];
                }
            }else{
                if(L1[j]){
                    // 单个Node.val范围是[0,9]
                    result = L2[i]+L1[j];
                    if(result < 10){
                        sum[i] = sum[i]+result;
                    }else{
                        sum[i] = sum[i]+(result%10);
                        next = i+1;
                        sum[next] = result / 10;
                    }
                }else{
                    sum[i] = L2[i];
                }
            }
        }
    }
}