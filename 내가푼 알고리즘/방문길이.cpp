#include <string>
using namespace std;

int solution(string dirs) {
    bool visited[12][12][12][12]={0,};
    int answer = 0;
    int x=5;
    int y=5;
    int cnt=0;
    for(int i=0;i<dirs.size();i++){
        if('U'==dirs[i]){
            if(y<10){
            if(visited[x][y][x][y+1]==0){
                visited[x][y][x][y+1]=1;
                visited[x][y+1][x][y]=1;
                cnt++;
            }
                printf("from x:%d y:%d\n",x,y); 
                x=x;
                y=y+1;   
                printf("to x:%d y:%d\n",x,y); 
        }   
            }
        else if('L'==dirs[i]){
            if(x>0){
                if(visited[x][y][x-1][y]==0){
                    visited[x][y][x-1][y]=1;
                    visited[x-1][y][x][y]=1;
                    cnt++;
                }
                    printf("from x:%d y:%d\n",x,y); 
                    x=x-1;
                    y=y;
                    printf("to x:%d y:%d\n",x,y);       
                }
        }
        else if('R'==dirs[i]){
            if(x<10){
            if(visited[x][y][x+1][y]==0){
                visited[x][y][x+1][y]=1;
                visited[x+1][y][x][y]=1;
                cnt++;
            }
                printf("from x:%d y:%d\n",x,y); 
                x=x+1;
                y=y;   
                printf("to x:%d y:%d\n",x,y);     
            }
        }
        else if('D'==dirs[i]){
            if(y>0){
                if(visited[x][y][x][y-1]==0){
                visited[x][y][x][y-1]=1;
                visited[x][y-1][x][y]=1;
                cnt++;
            }
                printf("from x:%d y:%d\n",x,y); 
                x=x;
                y=y-1; 
                printf("to x:%d y:%d\n",x,y);     
            }
        }
    printf("cnt:%d\n",cnt);            
    }   
    answer=cnt;
    return answer;
}
