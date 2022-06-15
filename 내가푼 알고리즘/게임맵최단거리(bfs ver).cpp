#include<vector>
#include <stdio.h>
#include<algorithm>
#include <queue>
#include <tuple>
using namespace std;

int visited[100][100];
int answer;
int cord_x;
int cord_y;

typedef struct Pos{
    int x;
    int y;
    int cnt;
}pos;



int bfs(vector<vector<int> > maps){

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    int x=0;
    int y=0;
    int cnt=1;
    queue<pos> q;
    visited[x][y]=1;
    q.push(pos({x,y,cnt}));
    while(!q.empty()){
        x=q.front().x;
        y=q.front().y;
        cnt=q.front().cnt;
        
        if(x==maps.size()-1&&y==maps[0].size()-1){
         //   printf("end\n");
            answer=cnt;
           return answer;
        }
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];   
           
            if(ny>=0&&nx>=0&&nx<maps.size()&&ny<maps[0].size()){
                if(visited[nx][ny]==0&&maps[nx][ny]==1){
                    visited[nx][ny]=1;
                    int n_cnt=cnt+1;
                    
                    // printf("x%d,y%d cnt:%d \n",nx,ny,n_cnt);
                    q.push(pos({nx,ny,n_cnt}));
                }
            }
        }
    }
 //   printf("hello\n");
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
//    printf("cord_x:%d,cord_y:%d\n",cord_x,cord_y);
    visited[0][0]=1;
    answer=bfs(maps);
    return answer;
}
