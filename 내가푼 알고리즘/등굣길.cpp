#include <string>
#include <vector>
#include <queue>
using namespace std;


int solution(int m, int n, vector<vector<int>> puddles) {
    int answer=0;
    //dp 선언
    vector<vector<int>> dp;
    vector<vector<bool>> visited;
    //dp초기화
    dp.assign(n, vector<int>(m,-1));
    visited.assign(n, vector<bool>(m,false));
    
    for(int i=0;i<puddles.size();i++){
        dp[puddles[i][1]-1][puddles[i][0]-1]=0;
    }
    
    dp[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(dp[i][j]==-1){
                if(i!=0&&j!=0)dp[i][j]=(dp[i-1][j]+dp[i][j-1])% 1000000007;
                else if(i!=0&&j==0)dp[i][j]=dp[i-1][j]%1000000007;  
                else if(i==0&&j!=0)dp[i][j]=dp[i][j-1]% 1000000007;
            }
        }
    }
   answer=dp[n-1][m-1];
    return answer;
}
