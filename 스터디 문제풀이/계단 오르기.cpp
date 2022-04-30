#include<iostream>
 
#define endl "\n"
#define MAX 301
using namespace std;
 
int N;
int Arr[MAX];    // 계단을 나타내는 배열
int DP[MAX];    // 해당 계단까지의 Max값을 나타내는 배열
 
int Max(int A, int B) { if (A > B) return A; return B; }
 
void Input()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> Arr[i];
    }
}
 
void Solution()
{
    DP[1] = Arr[1];    // 첫 번째 계단까지의 Max 값은 첫번째 계단 값이지
    DP[2] = Arr[1] + Arr[2];
    DP[3] = Max(Arr[1] + Arr[3], Arr[2] + Arr[3]);
    
    for (int i = 4; i <= N; i++)
    {
        DP[i] = Max(DP[i - 2] + Arr[i], DP[i - 3] + Arr[i-1] + Arr[i]);
    }
 
    cout << DP[N] << endl;
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

