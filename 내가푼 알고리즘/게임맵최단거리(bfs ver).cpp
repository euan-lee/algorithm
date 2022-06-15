#include<vector>
#include <stdio.h>
#include<algorithm>
#include <queue>
using namespace std;

int visited[100][100];
int answer;
int cord_x;
int cord_y;

int bfs(vector<vector<int> > maps){
    
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    int x=0;
    int y=0;
    queue<pair<int,int>> q;
    visited[x][y]=1;
    q.push(make_pair(0,0));
    while(!q.empty()){
        x=q.front().first;
        y=q.front().second;
        printf("x%d,y%d\n",x,y);
        if(x==maps.size()-1&&y==maps[0].size()-1){
            printf("end\n");
           return 11;
        }
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];   
            if(ny>=0&&nx>=0&&nx<maps.size()&&ny<maps[0].size()){
                if(visited[nx][ny]==0&&maps[nx][ny]==1){
                    visited[nx][ny]=1;
                    q.push(make_pair(nx,ny));
                }
            }
        }
    }
    printf("hello\n");
    return -1;  
}

int solution(vector<vector<int> > maps)
{
    
    answer = 0;
    for(int i=0;i<maps.size();i++){
        for(int j=0;j<maps[0].size();j++){
            visited[i][j]=0;
        }   
    }
    printf("cord_x:%d,cord_y:%d\n",cord_x,cord_y);
    visited[0][0]=1;
    answer=bfs(maps);
    return answer;
}
