#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

// 동 서 남 북
int dy[] = {0, 0, 1, -1};
int dx[] = {1, -1, 0, 0};

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY)
{
    int answer = 0;
    
    // 1. 캐릭터 좌표, 아이템 좌표 모두 2배로 늘린다.
    characterX *= 2, characterY *= 2, itemX *= 2, itemY *= 2;
    // board: 직사각형을 표현할 배열이다.(문제에 직사각형을 나타내는 모든 좌표값은 50이하라고 했지만, 
    // 우리는 모든 좌표값에 대해 2배를 할 것이므로 50*2=100이므로 좌표값은 최대 100이 될 것이다.)
    vector<vector<int>> board(110, vector<int>(110));
    
    // 직사각형의 시작점과 끝점
    int x1, y1, x2, y2;
    
    // 2. 직사각형을 board 배열에 모두 입력해준다.
    for (int i = 0; i < rectangle.size(); i++)
    {
        for (int j = 0; j < rectangle[0].size(); j++)
            rectangle[i][j] = rectangle[i][j] * 2;

        x1 = rectangle[i][0], y1 = rectangle[i][1];
        x2 = rectangle[i][2], y2 = rectangle[i][3];

        for (int y = y1; y <= y2; y++)
            for (int x = x1; x <= x2; x++)
                board[y][x] = 1;
    }

    // 3. 직사각형의 내부는 모두 0으로 채워준다.
    for (int i = 0; i < rectangle.size(); i++)
    {
        x1 = rectangle[i][0], y1 = rectangle[i][1];
        x2 = rectangle[i][2], y2 = rectangle[i][3];

        for (int y = y1 + 1; y < y2; y++)
            for (int x = x1 + 1; x < x2; x++)
                board[y][x] = 0;
    }

    // 4. BFS
    queue<pair<int, int>> q;
    q.emplace(characterY, characterX);
    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        if (y == itemY && x == itemX)
            break;

        for (int i = 0; i < 4; i++)
        {
            int nextY = y + dy[i];
            int nextX = x + dx[i];

            if (board[nextY][nextX] == 1)
            {
                q.emplace(nextY, nextX);
                board[nextY][nextX] = board[y][x] + 1;
            }
        }
    }

    // 좌표를 모두 2배로 늘려서 계산했으니 answer에는 2로 나눈 아이템의 좌표값을 넣어주면 정답이다.
    answer = board[itemY][itemX] / 2;
    return answer;
}

int main()
{
    vector<vector<int>> rectangle = {{1, 1, 7, 4}, {3, 2, 5, 5}, {4, 3, 6, 9}, {2, 6, 8, 8}};
    int characterX = 1;
    int characterY = 3;
    int itemX = 7;
    int itemY = 8;

    solution(rectangle, characterX, characterY, itemX, itemY);
}
