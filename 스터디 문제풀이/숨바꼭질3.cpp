#include<iostream>
#include<queue>
 
#define endl "\n"
#define MAX 100000 + 1
#define INF 999999999
using namespace std;
 
int N, K;
int Visit[MAX];
 
void Input()
{
    cin >> N >> K;
    for (int i = 0; i < MAX; i++)
    {
        Visit[i] = INF;
    }
}
 
int BFS()
{
    queue<int> Q;
    Q.push(N);
    Visit[N] = 0;
 
    while (Q.empty() == 0)
    {
        int Pos = Q.front();
        Q.pop();
 
        if (Pos == K) return Visit[K];
        
        if (Pos + 1 < MAX && Visit[Pos + 1] > Visit[Pos] + 1)
        {
            Visit[Pos + 1] = Visit[Pos] + 1;
            Q.push(Pos + 1);
        }
 
        if (Pos - 1 >= 0 && Visit[Pos - 1] > Visit[Pos] + 1)
        {
            Visit[Pos - 1] = Visit[Pos] + 1;
            Q.push(Pos - 1);
        }
 
        if (Pos * 2 < MAX && Visit[Pos * 2] > Visit[Pos])
        {
            Visit[Pos * 2] = Visit[Pos];
            Q.push(Pos * 2);
        }
    }
}
 
void Solution() 
{
    int R = BFS();
    cout << R << endl;
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
