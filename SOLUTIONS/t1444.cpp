#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// 结构体：点
struct Node
{
    int x, y, id;
} arr[30000];

Node node;

// 返回一个点的模长
int modulus(Node n){
    return n.x * n.x + n.y * n.y;
}

int cmp(Node a, Node b){
    // 如果共线，则比模长
    if (a.x * b.y - a.y * b.x == 0 && a.x * b.x + a.y * b.y >= 0){
        return modulus(a) < modulus(b);
    }
    // 不共线，则比弧度
    return atan2(a.y, a.x) < atan2(b.x , b.y);
}

int main(){
    // 写入n
    int n;
    std::cin >> n;

    // 写入每一个点的坐标
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i].x >> arr[i].y;
        arr[i].id = i+1;
    }
    
    // 以arr[0]作为坐标原点，将所有点坐标进行坐标变换
    for (int i = 0; i < n; i++)
    {
        arr[i].x -= arr[0].x;
        arr[i].y -= arr[0].y;
    }

    // 将所有的向量按弧度逆时针排布，若相等则按照模长小到大排布
    std::sort(arr, arr+n, cmp);

    // 进行迭代找到bunghole的start point
    int start = 0;// 默认第一个点起始，直到找到合适的点
    for (int i = 0; i < n - 1 ; i++)
    {
        // 比较两个点和原点形成的向量是否满足逆时针方向排列
        // 定义原点和相邻的两点
        Node ori = arr[0];
        Node n1 = arr[i];
        Node n2 = arr[i+1];
        // 计算向量
        int vec1x = n1.x - ori.x;
        int vec1y = n1.y - ori.y;
        int vec2x = n2.x - ori.x;
        int vec2y = n2.y - ori.y;
        int cross = vec1x * vec2y - vec2x * vec1y;
        int dot = vec1x * vec2x + vec2x * vec2y;
        // 判断是否符合逆时针排列
        if (cross < 0 || (cross == 0 && dot < 0))
        {
            // 如果是则作为凸包的起点
            start = i;
            break;
        } // 否则使用原点作为起点
    }
    // 打印结果
        std::cout << n << std::endl;
        std::cout << arr[0].id << std::endl; // 默认从第一个南瓜开始
        // 迭代，找到凸包上下一个点的索引
        for (int i = 0; i < n-1; i++)
        {
            int next = arr[(start + i)%(n -1) + 1].id;
            std::cout << next << std::endl;
        }
        

    
}
