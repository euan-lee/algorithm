#include <iostream>
 
#define endl "\n"
#define MAX 110
using namespace std;
 
int N, K;
int Weight[MAX];
int Value[MAX];
int DP[MAX][100010];
 
int Max(int A, int B) { if (A > B) return A; return B; }
 
void Input()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        cin >> Weight[i] >> Value[i];
    }
}
 
void Solution()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            if (j >= Weight[i])    DP[i][j] = Max(DP[i - 1][j], DP[i - 1][j - Weight[i]] + Value[i]);
            else DP[i][j] = DP[i - 1][j];
        }
    }
    cout << DP[N][K] << endl;
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
