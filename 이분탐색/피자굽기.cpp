#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 300005
#define INF 1e9+10

int n, d, arr[MAX], pizza[MAX], ans, minn = INF;
stack<int>s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> d >> n;
	for (int i = 0; i < d; i++) {
		cin >> arr[i];
		
		if (minn > arr[i]) minn = arr[i];
		else arr[i] = minn;
	}
	for (int i = 0; i < n; i++) cin >> pizza[i];

	for (int i = 0; i < d; i++)
	{
		if (pizza[0] > arr[i]) break;
		s.push(arr[i]);
	}

	int now = 0;
	while (!s.empty() && now < n) {
		if (s.top() >= pizza[now]) {
			ans = s.size(); now++;
		}
		s.pop();
	}

	if (now == n) cout << ans;
	else cout << 0;
}
