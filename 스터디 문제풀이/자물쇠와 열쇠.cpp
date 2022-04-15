#include <vector>
using namespace std;

int N,M;
vector<vector<int>> board;

// 잠금 해제 여부 체크
bool check(vector<vector<int>>& key, int y, int x){
    bool ret = true;

    // 보드판에 열쇠 값 적용
    for(int i=y;i<y+M;i++)
        for(int j=x;j<x+M;j++)
            board[i][j]+=key[i-y][j-x];

    // 자물쇠의 모든 좌표 확인
    for(int i=M;i<M+N;i++){
        for(int j=M;j<M+N;j++){
            if(board[i][j]!=1){
                ret=false;
                break;
            }
        }
        if(!ret) break;
    }

    // 보드판에 열쇠 값 해제
    for(int i=y;i<y+M;i++)
        for(int j=x;j<x+M;j++)
            board[i][j]-=key[i-y][j-x];

    return ret;
}

// 열쇠 시계방향 회전
void rotate(vector<vector<int>>& key){
    vector<vector<int>> temp(M,vector<int>(M));

    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
            temp[i][j] = key[j][M-i-1];

    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++)
            key[i][j] = temp[i][j];
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;

    M = key.size();
    N = lock.size();

    board = vector<vector<int>>(2*M+N,vector<int>(2*M+N));

    // 보드판에 좌물쇠 입력
    for(int i=M;i<M+N;i++)
        for(int j=M;j<M+N;j++)
            board[i][j]=lock[i-M][j-M];

    // 보드판의 모든 좌표에서 4방향에 대한 완전탐색
    for(int i=0;i<N+M;i++){
        for(int j=0;j<N+M;j++){
            for(int k=0;k<4;k++){
                rotate(key);
                if(check(key,i,j)){
                    answer = true;
                    break;
                }
            }
            if(answer) break;
        }
        if(answer) break;
    }

    return answer;
}
