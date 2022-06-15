#include<vector>
#include <stdio.h>
#include<algorithm>
using namespace std;

int visited[100][100];
int answer;
int cord_x;
int cord_y;
int cord_flag;

void dfs(int x,int y,int cnt,vector<vector<int> > maps){
   // printf("x%d,y%d\n",x,y);
    int min_ans=1000000;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    int nx=0;
    int ny=0;
    if(x==cord_x-1&&y==cord_y-1){
        min_ans=min(min_ans,cnt);
        answer=min_ans;
        cord_flag=1;
        return;
    }
    
    for(int i=0;i<4;i++){
        nx=x+dx[i];
        ny=y+dy[i];
        if(ny>=0&&nx>=0&&nx<cord_x&&ny<cord_y){
            if(maps[nx][ny]!=0&&visited[nx][ny]!=1){
                visited[nx][ny]=1;
                cnt++;
                dfs(nx,ny,cnt,maps);  
                cnt--;
                visited[nx][ny]=0;
            }
        }
    }
}

int solution(vector<vector<int> > maps)
{
    
    answer = 0;
    cord_y=maps[0].size();
    cord_x=maps.size();
    cord_flag=0;
    for(int i=0;i<cord_x;i++){
        for(int j=0;j<cord_y;j++){
            visited[i][j]=0;
        }   
    }
    
    visited[0][0]=1;
    dfs(0,0,1,maps);
    if(cord_flag==0){
        return -1;
    }
    return answer;
}
