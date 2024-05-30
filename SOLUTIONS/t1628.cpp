#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(pair<int, int>a, pair<int, int>b)
{
    return a.second == b.second ? a.first < b.first : a.second <b.second;
}

int main()
{
    // Size of the calendar and the number of unlucky days in it
    int m, n, k;
    cin >> m >> n >> k;

    // The  black of black
    vector<pair<int, int>> black;
    // The red cell (Possible singular  black that we encounter)
    vector<pair<int, int>> reds;

    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
     black.push_back({x, y});
    }

    // Initialize the answer
    int ans = 0;

    // Add sentinel point(Top left and bottom right)
    black.push_back({1, 0});
    black.push_back({m, n+1});
    sort(black.begin(), black.end());

    // For all the Rows
    for (int i = 1; i < black.size(); i++)
    {
        int dx = black[i].first - black[i-1].first;
        int dy = black[i].second - black[i - 1].second - 1; // Rows difference
        if (dx == 0) // In the same row 
        {
            if (dy == 1)
            {
                reds.push_back({black[i].first, black[i].second -1 });
            } else if (dy > 0)
            {
                ans ++;
            }
        }
        else // Not int same row
        {
            if (black[i].second ==2)
            {
                reds.push_back({black[i].first, 1});
            } else if (black[i].second > 2)
            {
                ans ++ ;
            }
            if (black[i - 1].second == n -1)
            {
                reds.push_back({black[i - 1].first, n});
            } else if (black[i - 1].second < n - 1)
            {
                ans ++;
            }
            if (n > 1)
            {
                ans += dx - 1; 
            } else if (dx == 2)
            {
                reds.push_back({black[i].first - 1, 1});
            }
        }
    }
    
    // For all the columns
    black.push_back({0, 1});
    black.push_back({m+1, n});
    sort(black.begin(), black.end(), cmp);

    for (int i = 2; i < black.size()-1; i++)
    {
        int  dy= black[i].second - black[i-1].second;
        int  dx= black[i].first - black[i-1].first - 1;
        if ( dy== 0)
        {
            if (dx == 1)
            {
                reds.push_back({black[i].first-1, black[i].second});
            } else if (dx > 0)
            {
                ans++;
            }
        }
        else
        {
            if (black[i].first == 2)
            {
                reds.push_back({1, black[i].second});
            } else if (black[i].first > 2)
            {
                ans ++;
            } 
            if (black[i-1].first == m-1)
            {
                reds.push_back({m, black[i-1].second});
            } else if (black[i-1].first < m-1)
            {
                ans ++;
            }
            if (m > 1)
            {
                ans += dy - 1; 
            } else if (dy == 2)
            {
                reds.push_back({1, black[i].second -1 });
            }  
        }
        
    }
    
    sort(reds.begin(), reds.end());
    // Red points counted twice are streaks
    int dif = reds.end() - unique(reds.begin(), reds.end());
    cout << ans + dif << endl;

    return 0;
}
