#include<iostream>
#include<queue>
#include<vector>
 
#define endl "\n"
#define MAX 510
using namespace std;
 
int N;
int Entry[MAX], Build_Time[MAX];
int Result[MAX];
vector<int> V[MAX];
 
int Bigger(int A, int B) { if (A > B) return A; return B; }
 
void Input()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> Build_Time[i];
        while (1)
        {
            int a; cin >> a;
            if (a == -1) break;
            V[a].push_back(i);
            Entry[i]++;
        }
    }
}
 
void Solution()
{
    queue<int> Q;
    for (int i = 1; i <= N; i++)
    {
        if (Entry[i] == 0)
        {
            Q.push(i);
            Result[i] = Build_Time[i];
        }
    }
 
    while (Q.empty() == 0)
    {
        int Cur = Q.front();
        Q.pop();
 
        for (int i = 0; i < V[Cur].size(); i++)
        {
            int Next = V[Cur][i];
            Entry[Next]--;
 
            Result[Next] = Bigger(Result[Next], Result[Cur] + Build_Time[Next]);
            if (Entry[Next] == 0) Q.push(Next); 
        }
    }
 
    for (int i = 1; i <= N; i++) cout << Result[i] << endl;
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
 
    freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}
