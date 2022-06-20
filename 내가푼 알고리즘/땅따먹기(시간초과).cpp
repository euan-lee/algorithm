#include <iostream>
#include <vector>
#include <stdio.h>
#include<string.h> 
using namespace std;
int row[4];
int answer;

void dfs(int n,vector<vector<int> >land1){
    if(n==land1.size()){
        int sum=0;
        for(int i=0;i<land1.size();i++){
            int y=row[i];
            int x=i;
          //  printf("row [%d]:%d",i,row[i]);
           // printf("land1[%d][%d]:%d\n",x,y,land1[x][y]);
            sum=sum+land1[x][y];
        }
        answer=max(answer,sum);
      //  printf("sum:%d\n",answer);
        return;
    }
    for(int i=0;i<land1[0].size();i++){
        if(n>0){
            if(row[n]==-1&&(i!=row[n-1])){
                row[n]=i;
                dfs(n+1,land1); 
                row[n]=-1;
            }       
        }
        else if(n==0){
            if(row[n]==-1){
                row[n]=i;
                dfs(n+1,land1); 
                row[n]=-1;
            }
        }
    }
}


int solution(vector<vector<int>> land)
{
    answer = 0;
    memset(row,-1,sizeof(row));
    dfs(0,land);
    return answer;
}
