#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


using namespace std;

const int inf = 1000000000;
vector<pair<int, int>> *adjList; 
pair<string, int> *tele;
int n;

void add2adj(string s, int index, int xxx);
int search(int left, int right, string s);

int main()
{
  
    cin >> n;
    int time[10];
    tele = new pair<string, int>[n];

    for (int i = 0; i < 10; i++)
        cin >> time[i];
    
for (int i = 0; i < n; i++)
{
    char tmp[11];
    cin >> tmp;
    tele[i].first = tmp;
    tele[i].second = i; 
}
sort(tele, tele+n);

adjList = new vector<pair<int, int>>[n];
for (int i = 0; i < n; i++)
    add2adj(tele[i].first, tele[i].second, i);

int *dist = new int[n];
int *prev = new int[n];
fill(prev, prev+n, -1);
fill(dist, dist+n, inf);

dist[0] = 0;
set<pair<int, int>> S;
S.insert(make_pair(dist[0], 0));

// Dijkstra
while (!S.empty())
{
    int v = S.begin()->second;
    S.erase(S.begin());

    if (dist[v] == inf)
        break;
    
    for (int i = 0; i < adjList[v].size(); i++)
    {
        int to = adjList[v][i].first;
        int weight = time[(adjList[v][i].second)];
        if (dist[v] + weight < dist[to])
        {
            S.erase(make_pair(dist[to],to));
            dist[to] = dist[v] + time[(adjList[v][i].second)];
            prev[to] = v;
            S.insert(make_pair(dist[to], to));
        }
    }
}

if (dist[n-1] == inf)
{
    cout << "-1" ;
    return 0;
} else 
{
    vector<int> path;
    for (int i = n-1; i!=0; i = prev[i])
        path.push_back(i+1);
    path.push_back(1);
    cout << dist[n-1] << "\n" << (int)path.size() << "\n" ;
    for (int i = (int)path.size()-1; i>=0; i--)
        cout << path[i] << " " ;
}
    return 0;
}

// Function
void add2adj(string s, int index, int xxx)
{
    for (int i = 0; i < 10; i++)
    {
        char d = '0';
        for (int j=0; j<10; j++) {
            if ((d+j)!=s[i]) {
                string tmp = s;
                tmp[i] = d + j;
                int result = search(xxx + 1, n-1, tmp);
                if (result != -1) {
                    adjList[index].push_back(make_pair(result, i));
                    adjList[result].push_back(make_pair(index, i));
                }
            }
            if (i < j && s[i] != s[j]) {
                string tmp = s;
                char x = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = x;
                int result = search(xxx + 1, n-1, tmp);
                if (result != -1) {
                    adjList[index].push_back(make_pair(result, i));
                    adjList[result].push_back(make_pair(index, i));
                }
            }
        }
    }
    
}

int search(int left, int right, string s)
{
    while (left < right) 
    {
        int middle = (left+right)/2;
        if (s <= tele[middle].first) 
        {
            right = middle;
        } else 
        {
            left = middle + 1;
        }
    }
    if (tele[right].first == s) 
    {
        return tele[right].second;
    } else 
    {
        return -1;
    }
}
