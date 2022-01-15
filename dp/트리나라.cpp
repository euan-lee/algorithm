#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int n, k;
long long dp[51][51][51];
bool chk[1000001];
vector<int> tmp[51], v[51];

void dfs(int now, int parent) { //부모-자식 관계 만들기
	for (int next = 0; next < tmp[now].size(); next++) {
		if (tmp[now][next] == parent) continue;
		v[now].push_back(tmp[now][next]);
		dfs(tmp[now][next], now);
	}
}

long long dpdp(int x, int t, int k) {
	long long& res = dp[x][t][k];
	if (res != -1) return res; //이미 계산한 값은 패스
	if (k == 0) return 1; //k개 도시를 다 골랐으면 끝
	if (t == v[x].size()) { //더 이상 탐색할 도시가 없을 때
		if (k == 1) return 1; //k가 1남았으면 루트 x를 고르는 경우 한 가지
		else return 0; //그 외의 경우는 없다
	}

	res = 0;
	for (int i = 0; i < k; i++) {
		res += dpdp(v[x][t], 0, i) * dpdp(x, t + 1, k - i);
		res %= 1000000007;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	for (int i = 0, a, b; i < n - 1; i++) {
		cin >> a >> b;
		a--; b--; //0부터 시작
		tmp[a].push_back(b);
		tmp[b].push_back(a);
	}
	dfs(0, -1); //부모자식관계 트리를 만든다
	memset(dp, -1, sizeof(dp));
	long long ans = 0;
	for (int i = 0; i < n; i++) { //모든 정점에 대해 계산한다
		ans += dpdp(i, 0, k);
	}
	cout << ans % 1000000007;
	return 0;
}