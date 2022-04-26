#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <cmath>

using namespace std;

// N = 0 , S = 1
vector<deque<int>> gear(5);
int rotation[5];
bool check[5];
int k;

// 각 톱니바퀴의 회전방향을 구한다.
void setRotation(int g, int d)
{
    rotation[g] = d;
    check[g] = true;
    // 현재 톱니바퀴의 왼쪽 톱니바퀴 세팅
    if (g - 1 > 0 && !check[g - 1])
    {
        // 현재 톱니바퀴가 회전하지 않으면
        if (d == 0)
            setRotation(g - 1, 0);
        // 맞닿은 극이 같다면
        else if (gear[g][6] == gear[g - 1][2])
            setRotation(g - 1, 0);
        // 맞닿은 극이 다르면
        else
            setRotation(g - 1, -d);
    }
    // 현재 톱니바퀴의 오른쪽 톱니바퀴 세팅
    if (g + 1 <= 4 && !check[g + 1])
    {
        // 현재 톱니바퀴가 회전하지 않으면
        if (d == 0)
            setRotation(g + 1, 0);
        // 맞닿은 극이 같다면
        else if (gear[g][2] == gear[g + 1][6])
            setRotation(g + 1, 0);
        // 맞닿은 극이 다르면
        else
            setRotation(g + 1, -d);
    }
}

// 각 톱니바퀴 회전 수행
void rotate()
{
    for (int i = 1; i <= 4; i++)
    {
        if (rotation[i] == 0)
            continue;
        // 시계 방향 회전
        if (rotation[i] == 1)
        {
            int temp = gear[i].back();
            gear[i].pop_back();
            gear[i].push_front(temp);
        }
        // 반시계 회전
        else
        {
            int temp = gear[i].front();
            gear[i].pop_front();
            gear[i].push_back(temp);
        }
    }
}

int getScore()
{
    int ans = 0;
    for (int i = 1; i <= 4; i++)
    {
        // 12시 방향이 S극
        if (gear[i][0] == 1)
        {
            ans += pow(2, i - 1);
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    char n;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> n;
            gear[i].push_back(n - '0');
        }
    }

    cin >> k;
    int g, d;

    while (k--)
    {
        cin >> g >> d;
        memset(check, false, sizeof(check));
        setRotation(g, d);
        rotate();
    }
    int ans = getScore();
    cout << ans << '\n';

    return 0;
}
