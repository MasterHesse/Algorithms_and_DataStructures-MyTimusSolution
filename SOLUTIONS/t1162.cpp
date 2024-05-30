#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
    int a, b; // Two nodes of an edge
    double r, c; // ExPoint and commissions
};

std::vector<edge> v;
double nodes[101];

int ret(bool b)
{
    cout << (b ? "YES" : "NO") << "\n";
    return 0;
}

int main()
{
    int N, M, S;
    double V;
    cin >> N >> M >> S >> V;

    nodes[S] = V;
    for (int i = 0; i < M; i++)
    {
        int a,b;
        double rab, cab, rba, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;

        v.push_back({a, b, rab, cab});
        v.push_back({b, a, rba, cba});
    }

    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < v.size();j++ )
            nodes[v[j].b] = std::max((nodes[v[j].a] - v[j].c)*v[j].r, nodes[v[j].b]);

    for (int i =0; i < v.size(); i++)
        if ((nodes[v[i].a]-v[i].c)*v[i].r > nodes[v[i].b] + 0.000001)
            return ret(true);
    return ret(false);
    
}