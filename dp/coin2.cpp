#include <iostream>
#include <algorithm>
using namespace std;
int coin[101];
int dp[100001];
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> coin[i];
	fill(dp, dp+100001, 100001);
	dp[0] = 0;
	for (int i = 1; i <= n; i++){
		for (int j = coin[i]; j <= k; j++)
			dp[j] = min(dp[j], dp[j - coin[i]] + 1);
	}
	dp[k] = (dp[k] == 100001) ? -1 : dp[k];
	cout << dp[k] << endl;
	return 0;
}