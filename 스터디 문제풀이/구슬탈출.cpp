#include<iostream>
#include<string>
#include<queue>
using namespace std;
 
int N, M;
int rx, ry, bx, by; // 공의 위치
int hx, hy; // 구멍의 위치
bool flag;
int ans = 0; // 탐색 횟수
char board[11][11]; // 보드
int visited[11][11][11][11]; // rx, ry, bx, by 위치에 따른 방문 여부 배열
queue<pair<int, int>> redball;
queue<pair<int, int>> blueball;
 
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
 
int main(void)
{
    string str;
    cin >> N >> M;
 
    for (int i = 0; i < N; i++)
    {
        cin >> str;
        for (int j = 0; j < M; j++)
        {
            board[i][j] = str[j];
            if (board[i][j] == 'R') {
                redball.push(make_pair(i, j)); rx = i, ry = j;
            }
            if (board[i][j] == 'B') {
                blueball.push(make_pair(i, j)); bx = i, by = j;
            }
            if (board[i][j] == 'O') hx = i, hy = j;
        }
    }
 
    visited[rx][ry][bx][by] = true;
 
    while (!redball.empty())
    {
        int qsize = redball.size();
 
        while (qsize--)
        {
            rx = redball.front().first;
            ry = redball.front().second;
            bx = blueball.front().first;
            by = blueball.front().second;
            redball.pop(); blueball.pop();
 
            // 10번 이상 탐색했으면 break
            if (ans > 10) break;
            // 빨간 구슬이 구멍에 빠지면 break
            if (rx == hx && ry == hy) { flag = true; break;}
 
            for (int i = 0; i < 4; i++)
            {
                int nrx = rx + dx[i];
                int nry = ry + dy[i];
                int nbx = bx + dx[i];
                int nby = by + dy[i];
 
                // 상하좌우 방향으로 구슬 움직이기
                while (1)
                {
                    if (board[nrx][nry] == '#') {
                        nrx -= dx[i]; nry -= dy[i];
                        break;
                    }
                    if (board[nrx][nry] == 'O') break;
                    nrx += dx[i]; nry += dy[i];
                }
                while (1)
                {
                    if (board[nbx][nby] == '#') {
                        nbx -= dx[i]; nby -= dy[i];
                        break;
                    }
                    if (board[nbx][nby] == 'O') break;
                    nbx += dx[i]; nby += dy[i];
                }
 
                // 파란 구슬이 구멍에 빠지면 continue
                if (nbx == hx && nby == hy) continue;
 
                // 같은 위치에 두 개의 구슬이 있으면 위치 갱신
                if (nrx == nbx && nry == nby)
                {
                    switch (i){
                    case 0: rx > bx ? nrx++ : nbx++; break;
                    case 1: rx < bx ? nrx-- : nbx--; break;
                    case 2: ry > by ? nry++ : nby++; break;
                    case 3: ry < by ? nry-- : nby--; break;
                    }
                }
                
                // 방문했던 지점이 아니면 push
                if (visited[nrx][nry][nbx][nby]) continue;
                redball.push(make_pair(nrx, nry));
                blueball.push(make_pair(nbx, nby));
                visited[nrx][nry][nbx][nby] = true;
            }
        }
        if (flag) break;
        else ans++;
    }
 
    if (flag) cout << 1;
    else cout << 0;
 
    return 0;
}
