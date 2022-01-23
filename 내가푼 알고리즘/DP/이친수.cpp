#include<iostream>
 
#define endl "\n"
typedef long long ll;
using namespace std;
 
ll N;
ll DP[91];
 
void Input()
{
    cin >> N;
}
 
void Solution()
{
    //1000 1001 1010 
    DP[0] = 0;
    DP[1] = 1;
    DP[2] = 1;
    for (int i = 3; i <= N; i++)
    {
        DP[i] = DP[i - 1] + DP[i - 2];
    }
}
 
void Solve()
{
    Input();
    Solution();
    cout << DP[N] << endl;
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
