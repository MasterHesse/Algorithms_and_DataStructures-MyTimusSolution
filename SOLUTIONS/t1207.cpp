#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <memory.h>
#include <algorithm>
#include <functional>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
using namespace std;

struct Node
{
    long long x, y, id;
} arr[10005];

bool cmp(Node a, Node b)
{
    Node vec1, vec2;
    vec1.x = a.x - arr[0].x;
    vec1.y = a.y - arr[0].y;
    vec2.x = b.x - arr[0].x;
    vec2.y = b.y - arr[0].y;

    return vec1.x * vec2.y - vec2.x * vec1.y > 0;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        scanf("%lld%lld", &arr[0].x, &arr[0].y);
        arr[0].id = 0;
        for (int i = 1; i < n; i++)
        {
            scanf("%lld%lld", &arr[i].x, &arr[i].y);
            arr[i].id = i;

            if (arr[i].x < arr[0].x)
                swap(arr[0], arr[i]);
            else if (arr[i].x == arr[0].x && arr[i].y < arr[0].y)
                swap(arr[0], arr[i]);
        }

        sort(arr + 1, arr + n, cmp);

        printf("%lld %lld\n", arr[0].id + 1, arr[n / 2].id + 1);
    }
}
