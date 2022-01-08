#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int N, K;
int p[50001];
int dp[50001][3]; 

int dfs(int idx, int cnt) {
	
	if (idx >= N || cnt == 3) return 0;
	if (dp[idx][cnt] != -1) return dp[idx][cnt];

	dp[idx][cnt] = 0;
	if (idx + K - 1 <= N)
		dp[idx][cnt] = max(dfs(idx + 1, cnt), dfs(idx + K, cnt + 1) + p[idx + K - 1] - p[idx - 1]);

	return dp[idx][cnt];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	for (int tmp, i = 1; i <= N; i++) {
		cin >> tmp;
		p[i] = p[i - 1] + tmp;
	}
		
	cin >> K;

	memset(dp, -1, sizeof(dp));
	cout << dfs(1, 0);
}

