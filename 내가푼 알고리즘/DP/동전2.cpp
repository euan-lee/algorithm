#include <iostream>
 
#define endl "\n"
#define MAX 110
using namespace std;
 
int N, K;
int Arr[MAX];
int DP[100010];
 
int Min(int A, int B) { if (A < B) return A; return B; }
 
void Input()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> Arr[i];
}
 
void Solution()
{
    for (int i = 1; i <= K; i++) DP[i] = 2e9;
    for (int i = 1; i <= N; i++) DP[Arr[i]] = 1;
    DP[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = Arr[i]; j <= K; j++)
        {
            DP[j] = Min(DP[j], DP[j - Arr[i]] + 1);
        }
    }
 
    if (DP[K] == 2e9) cout << -1 << endl;
    else cout << DP[K] << endl;
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