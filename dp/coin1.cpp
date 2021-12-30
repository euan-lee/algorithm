#include <iostream>
 
#define endl "\n"
#define MAX 110
using namespace std;
 
int N, K;
int Coin[MAX];
int DP[10010];
 
void Input()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> Coin[i];
}
 
void Solution()
{
    DP[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = Coin[i]; j <= K; j++)
        {
            DP[j] = DP[j] + DP[j - Coin[i]];
        }
    }
    cout << DP[K] << endl;
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

