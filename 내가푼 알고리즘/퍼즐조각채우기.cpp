#include <string>
#include <vector>
#include <queue>
using namespace std;

void Bfs(int x, int y,vector<vector<bool>>&visited,vector<vector<int>>&table,vector<pair<int,int>> &block){
    queue< pair<int,int> > q; 
    q.push(make_pair(x,y)); 
    visited[x][y] = true;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    int st_x=x;
    int st_y=y;
    while(!q.empty()){
        x = q.front().first;
        y = q.front().second;
        q.pop();
        block.push_back(make_pair(x-st_x,y-st_y));
        for(int i=0;i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(0<=nx&&nx<table.size()&&0<=ny&&ny<table[0].size()){
                if(table[nx][ny] == 1 && visited[nx][ny] == false){
                    visited[nx][ny]=true;
                    q.push(make_pair(nx,ny));   
                }
            }
        }
    }
}

void Rotation(vector<pair<int,int>> &block){
    for(int i=0;i<block.size();i++){
        int temp=block[i].first;
        block[i].first=-1*block[i].second;
        block[i].second=temp;
    }
}

bool FitCheck(int x,int y,vector<vector<int>> &game_board,vector<pair<int,int>> &block){
    printf("cord %d %d\n",x,y);
    printf("block-size:%d\n",block.size());
    for(int i=0;i<block.size();i++){//블럭[i]가 게임 보드 안에 들어있고 
            if(x+block[i].first>=0&&y+block[i].second>=0&&game_board[i].size()>x+block[i].first&&game_board[i].size()>y+block[i].second){
            }
            else{
                return false;
            }
        }
        for(int i=0;i<block.size();i++){//블럭이 들어갈수 있다면
            if(game_board[x+block[i].first][y+block[i].second]==1){//없다면
                return false;
           }    
        }
    return true;
}
void FillBlock(int x,int y,vector<vector<int>> &game_board,vector<pair<int,int>> &block){
    
}


int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
   
    //1.bfs 로 블록 구하기 ->시간복잡도 O(n*n) n=2500
    //이차원 visited vector를 table 만큼 생성
    vector<vector<bool>> visited(table.size(),vector<bool>(table[0].size())); 
    vector<vector<pair<int,int>>> blocks;   
    for(int i=0;i<table.size();i++){
        for(int j=0;j<table[0].size();j++){
            if(visited[i][j]==0&&table[i][j]==1){
                vector<pair<int,int>> block;   
                Bfs(i,j,visited,table,block);    
                blocks.push_back(block);
            }
             
        }
    }
    //visited_dfs->blocks사이즈만큼(최대 6개까지)
    vector<bool> visited_dfs(blocks.size(),false); 
    
    //dfs 처리(블럭의 순서도를 permutation으로 구한다.)
    for(int i=0;i<game_board.size();i++){//게임 보드 탐색하며 
        for(int j=0;j<game_board[i].size();j++){
            if(game_board[i][j]==0)
            for(int k=0;k<blocks.size();k++){//모든 블럭을 그 자리에 넣어본다.
                if(visited_dfs[k]==0){//만약 블럭k가 사용되지 않았고
                        for(int h=0;h<4;h++){
                            Rotation(blocks[k]);//k를 회전했을 떄
                            if(FitCheck(i,j,game_board,blocks[k])){//i,j자리에 맞는다면
                                //게임보드를 블럭자리에 1로 변경
                                FillBlock((i,j,game_board,blocks[k]));
                               // Permutation(i,j,visited_dfs,blocks);         

                                //게임보드를 블럭자리에 0으로 변경
                            }
                             printf("rotation end\n");
                        }
                }
            }       
        }    
    }
    
    int answer = 14;
    return answer;
}
