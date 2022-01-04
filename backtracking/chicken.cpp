#include<iostream>
#include<vector>
#include<cmath>
 
#define endl "\n"
#define MAX 50
using namespace std;
 
int N, M, Chicken_Num, Answer;
int MAP[MAX][MAX];
bool Select[13];
 
vector<pair<int, int>> House, Chicken, V;
 
int Min(int A, int B) { if (A < B) return A; return B; }
 
void Input()
{
    Answer = 99999999;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 1) House.push_back(make_pair(i, j));
            if (MAP[i][j] == 2) Chicken.push_back(make_pair(i, j));
        }
    }
    Chicken_Num = Chicken.size();
}
 
int Calculate_Distance()
{
    int Sum = 0;
    for (int i = 0; i < House.size(); i++)
    {
        int x = House[i].first;
        int y = House[i].second;
        int d = 99999999;
 
        for (int j = 0; j < V.size(); j++)
        {
            int xx = V[j].first;
            int yy = V[j].second;
            int Dist = abs(xx - x) + abs(yy - y);
 
            d = Min(d, Dist);
        }
        Sum = Sum + d;
    }
    return Sum;
}
 
void Select_Chicken(int Idx, int Cnt)
{
    if (Cnt == M)
    {
        Answer = Min(Answer, Calculate_Distance());
        return;
    }
 
    for (int i = Idx; i < Chicken_Num; i++)
    {
        if (Select[i] == true) continue;
        Select[i] = true;
        V.push_back(Chicken[i]);
        Select_Chicken(i, Cnt + 1);
        Select[i] = false;
        V.pop_back();
    }
}
 
void Solution()
{
    Select_Chicken(0, 0);
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