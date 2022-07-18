#include <string>
#include <vector>
#include <queue>
using namespace std;

int In_boundary(vector<pair<int,int>> &block,vector<vector<int>> &game_board,int r,int c){
  for(int i=0;i<block.size();i++){
      int x=block[i].first+r;
      int y=block[i].second+c;
      if(x>=0&&x<block.size()&&y>=0&&y<block[i].size()){
          continue;     
      }else{
          return 0;      
      }   
  }     
    return 1;
}

void Rotation(vector<pair<int,int>> &block){
    for(int i=0;i<block.size();i++){
        block[i].first=-block[i].second;
        block[i].second=block[i].first;
    }
}


void dfs(vector<vector<int>> &game_board,vector<vector<pair<int,int>>> blocks;,vector<int> &visited,int depth){
    
    if(blocks.size()==depth){
        return;
    }
    for(int i=0;i<game_board.size();i++){//게임 보드 위치 순회
        for(int j=0;j<game_board[i].size();j++){//게임 보드 위치 순회
            for(int k=0;k<blocks.size();k++){//테이블 사용여부 확인을 위해서
                if(game_board[i][j]!=1&&visited[k]==0){//만약 게임 보드가 비어있고 블럭을 쓸수 있다면~
                    for(int h=0;h<4;h++){//회전한 후
                        Rotation(blocks[k]);
                        if(In_boundary(blocks[k],game_board,i,j)){//범위 안에 들어온다면 
                           //game_board에 block을 위치시킴
                            for(int m=0;m<blocks[k].size();m++){
                            
                            }
                            //
                        }
                        visited[k]=1;
                        dfs(game_board,table,visited,depth+1);
                        visited[k]=0;
                        //game_board에 block을 원위치 시킴
                        for(int m=0;m<blocks[k].size();m++){
                            
                        }
                        //
                    } 
                }
            }
        }
    }
}


bool CheckMap(int x, int y,int r,int c){
    return (x >= 0 && x < r) && (y >=0 && y < c);
}

void Bfs(int x,int y,vector<vector<int>> &table,vector<pair<int,int>> &block){
    int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};     
    queue<pair<int,int>> q; 
    q.push(pair<int,int>(x,y)); 
    while(!q.empty()){
        int cur_r=q.front().first;        
        int cur_c=q.front().second; 
        q.pop();     
        for(int i=0;i<4;i++){
            int next_r=cur_r+dir[i][0];
            int next_c=cur_c+dir[i][1];
            if(CheckMap(next_r,next_c,table.size(),table[i].size())&&table[next_r][next_c]==1){
                table[next_r][next_c]=0;
                block.push_back({make_pair(next_r-x,next_c-y)});
                q.push(pair<int,int>(next_r,next_c));  
            }
        } 
    }
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    
    //1.bfs
    vector<vector<pair<int,int>>> blocks;   
    int cnt=-1;
    for(int i=0;i<table.size();i++){
        for(int j=0;j<table[i].size();j++){
            if(table[i][j]==1){
                vector<pair<int,int>> block;   
                Bfs(i,j,table,block);//table의 블록 나누기(1,1을 기준으로 좌표들을 구한다)    
                blocks.push_back(block);
            } 
        }
    }
    
    //2.dfs    
    int answer = -1; 
    vector<int> visited(table.size());//table.size()만큼 사이즈 0으로 할당
    dfs(game_board,table,visited,0);
    
    return answer;
}
