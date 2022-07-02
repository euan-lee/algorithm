#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int dp[500][500]={0,};
    dp[0][0]=triangle[0][0];
    dp[1][0]=triangle[1][0];
    dp[1][1]=triangle[1][1];
    for(int i=0;i<triangle.size();i++){
        for(int j=0;j<triangle[i].size();j++){
                if(j==0){
                    dp[i][j]=dp[i-1][j]+triangle[i][j];
                }else if(j==triangle[i].size()-1){
                    dp[i][j]=dp[i-1][j-1]+triangle[i][j];             
                }else{
                    dp[i][j]=triangle[i][j]+max(dp[i-1][j-1],dp[i-1][j]);  
                }   
        }
    }
    
    for(int i=0;i<triangle[triangle.size()-1].size();i++){
        answer=max(answer,dp[triangle.size()-1][i]);
    }
    return answer;
}

/*
         [00]
      [10] [11]
    [20] [21] [22]
  [30] [31] [32] [33]
[40] [41] [42] [43] [44]
*/
