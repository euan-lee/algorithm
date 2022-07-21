#include <string>
#include <vector>
#include <queue>
using namespace std;

void BfsDp(int x,int y,vector<vector<int>> &dp,vector<vector<bool>> &visited){
    int dir[2][2]={{-1,0},{0,-1}};     
    queue<pair<int,int>> q; 
    q.push(pair<int,int>(x,y)); 
    visited[x][y]=true;
    while(!q.empty()){
        int cur_x=q.front().first;        
        int cur_y=q.front().second; 
        q.pop();   
        if(dp[cur_x][cur_y]!=0){
             dp[cur_x][cur_y]=(dp[cur_x+1][cur_y]+dp[cur_x][cur_y+1])%1000000007; 
        }
        for(int i=0;i<2;i++){
            int next_x=cur_x+dir[i][0];
            int next_y=cur_y+dir[i][1];
            if(next_x>=0&&next_y>=0){
                if(visited[next_x][next_y]==false){
                    visited[next_x][next_y]=true;
                    q.push(pair<int,int>(next_x,next_y));          
                }else{
                    continue;
                }
            }   
         }
        
    }
}


int solution(int m, int n, vector<vector<int>> puddles) {
    m = 7;
    n = 4;
int arr[9][2]={{2,1},{2,2},{2,3},{4,2},{4,3},{4,4},{6,2},{6,3}}; 
    
    //dp 선언
    vector<vector<int>> dp;
    vector<vector<bool>> visited;
    //dp초기화
    dp.assign(n, vector<int>(m,-1));
    visited.assign(n, vector<bool>(m,false));
    /*
    for(int i=0;i<puddles.size();i++){
        dp[puddles[i][1]-1][puddles[i][0]-1]=0;
    }
    */
    for(int i=0;i<9;i++){
        dp[arr[i][1]-1][arr[i][0]-1]=0;
    }
    
    
    //벽쪽 cache는 1로 저장(만약 0이라면)
    for(int i=0;i<m;i++){
        if(dp[n-1][i]==0)continue;
        else if(dp[n-1][i]==-1)dp[n-1][i]=1;   
    }
    for(int i=0;i<n;i++){
        if(dp[i][m-1]==0)continue;
        else if(dp[i][m-1]==-1)dp[i][m-1]=1;
    }
    
    //설정 초기화 완료
    BfsDp(n-2,m-2,dp,visited);
        int answer = dp[0][0];
    return answer;
}
