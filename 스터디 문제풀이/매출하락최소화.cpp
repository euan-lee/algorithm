#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> tree[300001];
int dp[300001][2];
bool visited[300001];
//dp[][0]은 해당 사원이 포함 안됐을 때 최솟값, dp[][1]은 해당 사원이 포함 됐을 때 최솟값
void find(int n,const vector<int> &sales){
    dp[n][1]= sales[n-1];
    visited[n]=true;
    for(int i=0; i<tree[n].size(); i++){
        int child = tree[n][i];
        if(visited[child]) continue;
        find(child,sales);
        dp[n][1] += min(dp[child][0],dp[child][1]);
    }
    int tmpsum=0;
    bool issumed=false;
    vector<int> tmpvec;
    for(int i=0; i<tree[n].size();i++){
        int child=tree[n][i];
        if(dp[child][1]<dp[child][0]){
            issumed=true;
            tmpsum+=dp[child][1];
        }
        else{
            tmpvec.push_back(dp[child][1]-dp[child][0]);
            tmpsum+=dp[child][0];
        }
    }
    if(tree[n].size()>0){
        if(issumed) dp[n][0]=tmpsum;
        else{
            sort(tmpvec.begin(),tmpvec.end());
            dp[n][0]=tmpsum+tmpvec[0];
        }
    }
}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    for(auto a:links){
        tree[a[0]].push_back(a[1]);
    }
    find(1,sales);
    answer=min(dp[1][0],dp[1][1]);
    cout<<dp[1][0]<<" "<<dp[1][1];
    return answer;
}
