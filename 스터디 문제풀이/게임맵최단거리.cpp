#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> map;
vector<vector<int>> visited(101, vector<int>(101, 987654321));
int N, M;
int ROTATE_X[] = { 0, -1, 0, 1 };
int ROTATE_Y[] = { -1, 0, 1, 0 };

void BFS()
{
    queue<pair<int, int>> loc;
    int cur_x, cur_y;
    int next_x, next_y;

    loc.push(make_pair(0, 0));
    visited[0][0] = 1;

    while (!loc.empty())
    {
        cur_x = loc.front().first;
        cur_y = loc.front().second;
        loc.pop();
        for (int i = 0; i < 4; i++)
        {
            next_x = cur_x + ROTATE_X[i];
            next_y = cur_y + ROTATE_Y[i];

            if (next_x < 0 || next_x > N || next_y < 0 || next_y > M)
                continue;
            if (map[next_x][next_y] == 0)
                continue;
            if (visited[next_x][next_y] > visited[cur_x][cur_y] + 1)
            {
                visited[next_x][next_y] = visited[cur_x][cur_y] + 1;
                loc.push(make_pair(next_x, next_y));
            }
        }
    }
}

int solution(vector<vector<int>> maps)
{
    int answer = 0;
    map = maps;

    N = maps.size() - 1;
    M = maps[0].size() - 1;

    BFS();

    if (visited[N][M] == 987654321)
        answer = -1;
    else
        answer = visited[N][M];

    return answer;
}
