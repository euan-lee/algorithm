#include <iostream>
#include <algorithm>
using namespace std;
 
int maze[1001][1001];
int d[1001][1001];
int N,M;
 
// 방법3: top-down, 재귀 사용.
int dp(int r, int c){
    if(r == N && c == M) return maze[r][c];     //base value
    if(r > N || c > M) return 0;                //미로의 범위를 벗어나는 조건!
    if(d[r][c] >= 0) return d[r][c];            //메모이제이션(-1로 초기화)
    
    d[r][c] = max(dp2(r+1,c), dp2(r,c+1)) + maze[r][c];
    return d[r][c];
}
 
// 방법4: 여태껏 d를 채우는 방법이 [1,1]에서 [N,M]으로 가는 것이었다면, 현재 방법은 그 거꾸로 가는 것이다.
//  top-down, 재귀
int dp2(int r, int c){
    if(r == 1 && c == 1) return maze[1][1];     //base value
    if(r < 1 || c < 1) return 0;                //미로의 범위를 벗어나는 조건!
    if(d[r][c] >= 0) return d[r][c];            //메모이제이션(-1로 초기화)
    
    d[r][c] = max(dp(r-1,c), dp(r,c-1)) + maze[r][c];
    return d[r][c];
}
 
int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            cin >> maze[i][j];
        }
    }
    // 방법1: i,j로 올수 있는 방법은 2가지
    //          위에서 올 때 : d[i-1][j]
    //          왼쪽에서 올 때 : d[i][j-1]
    // 이 세가지 방법중 제일 큰 수를 현재 위치인 i,j에 저장한다.
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            d[i][j] = max(d[i-1][j],d[i][j-1]) + maze[i][j];
        }
    }
 
    // 방법2: i,j에서 갈 수 있는 방법 2가지
    //          아래로 갈 때: d[i+1][j] = d[i][j] + maze[i+1][j]
    //          오른쪽으로 갈 때: d[i][j+1] = d[i][j] + maze[i][j+1]
    d[1][1] = maze[1][1];
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            d[i+1][j] = max(d[i+1][j], d[i][j] + maze[i+1][j]);
            d[i][j+1] = max(d[i][j+1], d[i][j] + maze[i][j+1]);
        }
    }
    cout << d[N][M] << endl;
    return 0;
}
 
