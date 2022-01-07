#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int w[101]; // 무게
int v[101]; // 가치
int dp[101][100001];

int N, K; // 물품의 수 N, 준서가 버틸 수 있는 무게 K

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);
    
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		cin >> w[i] >> v[i];
	}
    
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			if (j - w[i] >= 0) { // i번째 물건을 넣을 수 있다면?
				dp[i][j] = max(dp[i-1][j], dp[i - 1][j - w[i]] + v[i]);
                // 넣지 않을 때와 넣었을 때, 둘 중 더 큰 것으로 초기화
			}
            else{ // i번째 물건을 넣을 수 없다면, 배낭 용량은 같고 넣지 않았을 때의 값으로 초기화
                dp[i][j] = dp[i-1][j];
            }
		}
	}

	cout << dp[N][K];

	return 0;
}
