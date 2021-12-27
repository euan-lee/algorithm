#include<iostream>
#include<vector>
 
#define endl "\n"
#define MAX 20010
#define INF 987654321
using namespace std;
 
int V, E, Start; 
int MAP[MAX][MAX];
int Dist[MAX];
bool Select[MAX];
 
int Min(int A, int B) { if (A < B) return A; return B; }
 
void Input()
{
    cin >> V >> E >> Start;
 
    for (int i = 1; i <= V; i++)
    {
        Dist[i] = INF;
        for (int j = 1; j <= V; j++)
        {
            if (i == j) MAP[i][j] = 0;
            else MAP[i][j] = INF;
        }
    }
 
    for (int i = 0; i < E; i++)
    {
        int a, b, c; cin >> a >> b >> c;
        MAP[a][b] = c;
    }
}
 
int Find_Shortest_Node()
{
    int Min_Dist, Min_Idx;
    Min_Dist = INF;
    Min_Idx = -1;
 
    for (int i = 1; i <= V; i++)
    {
        if (Select[i] == true) continue;
        if (Dist[i] < Min_Dist)
        {
            Min_Dist = Dist[i];
            Min_Idx = i;
        }
    }
    return Min_Idx;
}
 
void Update_Dist(int NewNode)
{
    for (int i = 1; i <= V; i++)
    {
        if (Select[i] == true) continue;
        if (Dist[i] > Dist[NewNode] + MAP[NewNode][i])
        {
            Dist[i] = Dist[NewNode] + MAP[NewNode][i];
        }
    }
}
 
void Dijkstra()
{
    for (int i = 1; i <= V; i++) Dist[i] = MAP[Start][i];
    Dist[Start] = 0;
    Select[Start] = true;
    
    for (int i = 0; i < V - 1; i++)
    {
        int NewNode = Find_Shortest_Node();
 
        Select[NewNode] = true;
        Update_Dist(NewNode);
    }
}
 
void Solution()
{
    Dijkstra();
    for (int i = 1; i <= V; i++)
    {
        if (Dist[i] == INF) cout << "INF" << endl;
        else cout << Dist[i] << endl;
    }
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

