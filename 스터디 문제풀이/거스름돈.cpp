#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(int a, int b)
{
    return a>b;
}

int answer = 0;

void dfs(int now,int index, vector<int> money)
{
    
    for(int i=index;i<money.size();i++)
    {
        if(now-money[i]>0)
        {
            dfs(now-money[i],i, money);
        }
        else if( now - money[i]==0)
        {
            answer++;
        }
    }
    
}


int solution(int n, vector<int> money) {

    sort(money.begin(),money.end(),cmp);
    
    dfs(n,0,money);
    return answer;
}
