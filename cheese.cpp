#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

struct pos
{
    int y, x;
};
int paper[101][101]; 
bool visit[101][101]; //방문 확인 
int outAir[101][101]; // 주변 바깥공기개수 카운트
int n, m;
int dy[] = {0, 1, 0, -1};
int dx[] = {-1, 0, 1, 0};

// input 함수
void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> paper[i][j];
        }
    }
}

// 바깥공기를 2로 할당해주는 과정, BFS사용
void spreadAir()
{
    queue<pos> q;
    q.push({0, 0});

    while (!q.empty())
    {
        pos cur = q.front();
        int y = cur.y;
        int x = cur.x;
        q.pop();
        if (visit[y][x])
            continue;
        visit[y][x] = true;

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= m)
                continue;
            // 현재 좌표가 바깥공기이므로 다음좌표는 바깥공기와 닿아있는것
            if (paper[ny][nx] == 1)
                outAir[ny][nx]++;
            else if (!visit[ny][nx])
                q.push({ny, nx});
        }
    }
}

// 녹는 치즈를 0으로 치환하는 과정
bool melt()
{
    bool isMelted = false;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (outAir[i][j] >= 2)
            {
                paper[i][j] = 0;
                isMelted = true;
            }
        }
    }
    return isMelted;
}

void solve()
{
    int t = 0;
    while (true)
    {
        // visit, outAir 초기화
        memset(visit, 0, sizeof(visit));
        memset(outAir, 0, sizeof(outAir));

        spreadAir(); 
        bool isMelted = melt();

        if (isMelted)
            t++;
        // 아무것도 녹지 않았다면 break
        else
            break;
    }
    cout << t << '\n';
}

int main()
{
    input();
    solve();

    return 0;
}
