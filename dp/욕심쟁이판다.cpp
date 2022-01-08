#include<iostream>
 
#define endl "\n"
#define MAX 500
using namespace std;
 
int N, Answer;
int MAP[MAX][MAX];
int DP[MAX][MAX];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
 
int Bigger(int A, int B) { return A > B ? A : B; }
 
void Input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }
}
 
int Move(int x, int y)
{
    if (DP[x][y] != 0) return DP[x][y];
    DP[x][y] = 1;
 
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
 
        if (nx >= 0 && ny >= 0 && nx < N && ny < N)
        {
            if (MAP[x][y] < MAP[nx][ny])
            {
                DP[x][y] = Bigger(DP[x][y], Move(nx, ny) + 1);
            }
        }
    }
    return DP[x][y];
}
 
void Solution()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Answer = Bigger(Answer, Move(i, j));
        }
    }
    cout << Answer << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    //freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}
