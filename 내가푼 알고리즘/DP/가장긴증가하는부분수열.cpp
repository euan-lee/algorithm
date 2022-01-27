#include <bits/stdc++.h>
using namespace std;
int dp[1001];
int arr[1001];
int main(void)
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
		dp[i] = 1;
	}

	int ans = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j])
			{
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		ans = max(ans, dp[i]);
	}

	cout << ans;
}
 

