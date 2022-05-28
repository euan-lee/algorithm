#include <string>
#include <vector>
 
using namespace std;
 
int N, M;
int dx[] = { 0, 1, 1 };
int dy[] = { 1, 0, 1 };
 
bool Check(int x, int y, vector<string> board)
{
    for (int i = 0; i < 3; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= N || ny >= M) return false;
        if (board[x][y] != board[nx][ny]) return false;
    }
    return true;
}
 
int Delete_Block(vector<pair<int, int>> V, vector<string> &board)
{
    int Cnt = 0;
    for (int i = 0; i < V.size(); i++)
    {
        int x = V[i].first;
        int y = V[i].second;
        if (board[x][y] != '.')
        {
            board[x][y] = '.';
            Cnt++;
        }
 
        for (int j = 0; j < 3; j++)
        {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if (board[nx][ny] != '.')
            {
                Cnt++;
                board[nx][ny] = '.';
            }
        }
    }
    return Cnt;
}
 
void Arrange_MAP(vector<string> &board)
{
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == '.') continue;
            
            int nx = i + 1;
            while (nx < N && board[nx][j] == '.') nx++;
            nx--;
            if (nx != i)
            {
                board[nx][j] = board[i][j];
                board[i][j] = '.';
            }
        }
    }
}
 
int solution(int m, int n, vector<string> board) 
{
    N = m;
    M = n;
    int answer = 0;
    bool Flag = true;
 
    while (Flag == true)
    {
        Flag = false;
        vector<pair<int, int>> V;
        vector<vector<bool>> Visit(N, vector<bool>(M, false));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (board[i][j] == '.') continue;
                if (Check(i, j, board) == true)
                {
                    V.push_back(make_pair(i, j));
                    Flag = true;
                }
            }
        }
 
        if (Flag == true)
        {
            answer = answer + Delete_Block(V, board);
            Arrange_MAP(board);
        }
    }
    return answer;
}
