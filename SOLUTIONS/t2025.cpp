#include <iostream>
#include <stdio.h>
using namespace std;

/*
    Team quantity: k,
    Total member: n,
    Number of tests: T.
*/ 
int T,n,k;

int fight(int n,int k){
    int count = 0;
    int *team = new int[k];
    for (int i = 0; i < k; i++)
    {
        team[i] = n/k;
    }
    if (n % k != 0)
    {
        int remain = n%k;
        for (int i = 0; i < k; i++)
        {
            team[i] += 1;
            remain -= 1;
            if (remain == 0)
            {
                break;
            }   
        }
        
    }

    for (int i = 0; i < k; i++)
    {
        count += team[i] * (n - team[i]); 
    }
    count = count/2;
    
    return count;
}

int main(){
    scanf("%d", &T);
    int *answer = new int[T];
    for (int i = 0; i < T; i++)
    {
        scanf("%d %d",&n,&k);
        answer[i] = fight(n,k);
    }
    for (int i = 0; i < T; i++)
    {
        cout << answer[i] << endl;
    }         
}
