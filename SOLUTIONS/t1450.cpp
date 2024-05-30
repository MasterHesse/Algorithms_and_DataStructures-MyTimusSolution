#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// C[i] max is 10000, N max is 500
// Thus minus infinite can be -500 * 10000
const int inf = -500 * 10000;

struct Node
{
    vector<pair<int, int>> e; // Edge out of this node with value
    int dist; // Max distance to this node so far
    int in; // Indegree

    Node() : in(0), dist(inf) {}
} nodes[501];

int main()
{
    int N, M, S, F;
    cin >> N >> M;

    queue<Node*> q; // Set of Nodes with no indegree

    for (int i = 0; i < M; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;

        nodes[A].e.push_back(make_pair(B, C));
        nodes[B].in++;
    }

    cin >> S >> F;

    // Inisualize the dist 
    nodes[S].dist = 0;

    for (int i = 0; i <= N; i++)
    {
        if (nodes[i].in == 0)
        {
            q.push(nodes + i); //Inisualize q
        }
    }
    
    while (!q.empty())
    {
        auto nod = q.front();
        q.pop();
        for (auto it = nod ->e.begin(); it < nod -> e.end(); it++)
        {
            nodes[it->first].dist = max(nodes[it->first].dist, nod->dist + it->second);
            nodes[it->first].in--;
            if (nodes[it->first].in == 0)
            {
                q.push(nodes + it->first);
            }
        }
    }
    
    if (nodes[F].dist >= 0)
    {
        cout << nodes[F].dist << endl;
    } else
    {
        cout << "No solution\n" << endl;
    }

    return 0;
}

