#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    int x[100005];
    int y[100005];


    // Read the num of member
    int n;
    cin >> n;
    int pair = (n*(n-1)/2); 

    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
        cin >> y[i];     
    }

    sort(x+1,x+n+1);
    sort(y+1,y+n+1);

    // calculate distance
    long long dist = 0;

    for (int i = 1; i < n; i++)
    {
        dist += ((x[i+1] - x[i]) +  (y[i+1] -y[i])) * i * (n-i);
        
    }
    

    dist = dist / (pair);

    cout << dist << endl;
    


    return 0;
}