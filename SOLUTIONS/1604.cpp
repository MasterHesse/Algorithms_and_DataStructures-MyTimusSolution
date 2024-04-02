#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;

class Compare {
public:
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        return (a.first == b.first) ? (a.second > b.second) : a.first < b.first;
    }
};

int main(){
    int type;
    scanf("%d", &type);
    
    // 使用优先队列存储速度限制标志，按剩余数量最多的标志数量排序
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    // 传入每个type中，sign的数量
    for (int i = 1; i <= type; i++) {
        int signCount;
        scanf("%d", &signCount);
        pq.push(make_pair(signCount, i));
    }

    // 依次输出
    while (!pq.empty()) {
        auto p1 = pq.top(); // 获取剩余数量最多的标志
        pq.pop();
        printf("%d ", p1.second); // 输出标志编号
        if (!pq.empty()) {
            auto p2 = pq.top();
            pq.pop();
            printf("%d ", p2.second);
            if (p2.first > 1) {
                pq.push(make_pair(p2.first - 1, p2.second)); // 将剩余数量减少1后重新插入优先队列
            }
        }
        if (p1.first > 1) {
            pq.push(make_pair(p1.first - 1, p1.second)); // 将剩余数量减少1后重新插入优先队列
        }
    }

    return 0;
}
