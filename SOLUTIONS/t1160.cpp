#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    node* parent;
    int rank; // 
    int id; //Number of this node
    
    node(): parent (this), rank(0) { }
};

struct edge
{
    node* a;
    node* b; 
    int weight;

    edge(node* a, node* b, int weight):
    a(a), b(b), weight(weight) { }
};

void link(node* a, node* b)
{
    if (a->rank > b->rank)
        b->parent = a;
    else
    {
        a->parent = b;
        if (a->rank == b->rank)
            b->rank++;
    }
}

node* find(node* s)
{
    if (s != s->parent)
        s->parent = find(s->parent);
    return s->parent;
}

void join(node* a, node*b)
{
    link(find(a), find(b));
}

bool cmp(edge& a, edge&b)
{
    return a.weight < b.weight;
}

vector<node> nodes;
vector<edge> edges;
vector<edge*> ans;

int main()
{
    int N, M;
    cin >> N >> M;
    nodes.reserve(N+1);

    for (int i = 0; i < N+1; i++)
    {
        nodes.push_back(node());
        nodes.back().parent = &nodes.back();
        nodes.back().id = i;
    }
    edges.reserve(M);
    ans.reserve(M);

    for (int i = 0; i < M; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        edges.emplace_back(&nodes[x], &nodes[y], w);
    }
    
    sort(edges.begin(), edges.end(), cmp);
    
    int max = 0;
    for(edge& e:edges)
    {
        if (find(e.a) != find(e.b))
        {
            join(e.a, e.b);
            max = std::max(max, e.weight);
            ans.push_back(&e);
        }
    }
    
    cout << max << "\n";
    cout << ans.size() << "\n";
    for (auto e: ans)
    {
        cout << e->a->id << " " << e->b->id << "\n";
    }

    return 0;
}