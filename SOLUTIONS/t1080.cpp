#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int RED = 0;
const int BLUE = 1;

bool isBipartite(vector<vector<int>>& graph, vector<int>&colors, int start)
{
    // Use BFS to traverse the graph and color the nodes
    queue<int> q;
    q.push(start);
    colors[start] = RED; // Color the first country as red

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        // Traverse the neighbors
        for (int neighbor : graph[current])
        {
            // Color it with the opposite colorof the current country
            if (colors[neighbor] == -1)
            {
                colors[neighbor] = 1 - colors[current];
                q.push(neighbor);
            }
            // If the neighboring got the same color
            else if (colors[neighbor] == colors[current])
            {
                return false;
            }
        }
    }
    
    return true;
}

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> graph(N); // Adjacency list for connection
    vector<int> colors(N, -1); // Array to store colors of country

    // Input connections for each country
    for (int i = 0; i < N; i++)
    {
        int country ;
        while (cin >> country && country != 0)
        {
            graph[i].push_back(country - 1);
            graph[country - 1].push_back(i);
        }
    }

    // Start coloring from the first
    if (!isBipartite(graph, colors, 0))
    {
        cout << -1 << endl;
    } else
    {
        for(int color : colors)
        {
            cout << color;
        }
        cout << endl;
    }
    return 0;
}