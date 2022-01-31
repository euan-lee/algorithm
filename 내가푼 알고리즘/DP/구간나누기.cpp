#include <iostream>
using namespace std;
#define MIN -3276800; 
int arr[101]; 
int dp[101][51]; 
int calculate(int n, int m) {
  if (m == 0) return 0; 
  if (n <= 0) return MIN;
  if (dp[n][m] != -1) return dp[n][m];
  int sum = 0; // 3: n번째 인덱스가 구간에 포함되지 않는 경우. 재귀이기 때문에 그 이전의 모든 경우의 수가 계산된다.
  dp[n][m] = calculate(n - 1, m); 
  for (int i = n; i > 0; i--) { 
    // 1: 누적합을 이용해서 1개의 구간을 구한다. (i부터 n까지의 구간)
    sum += arr[i]; // 2: 인접하지 않는 범위에서 m - 1개의 구간의 합의 최댓값을 구한다.
    int tmp = calculate(i - 2, m - 1) + sum; 
    if (tmp > dp[n][m]) { dp[n][m] = tmp; } }
  return dp[n][m]; } 

int main() { 
  int n, m; 
  cin >> n >> m; 
  for (int i = 1; i <= n; i++) {
    cin >> arr[i]; 
    for (int j = 1; j <= n / 2; j++) { 
      dp[i][j] = -1; 
    } }
  cout << calculate(n, m) << '\n'; return 0;
}
