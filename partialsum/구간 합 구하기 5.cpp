#include <iostream>
#include <algorithm>

using namespace std;

int p_sum[1025][1025];

int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, M, num;
	cin >> N >> M;

    // 구간합 표 구하기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> num;
			p_sum[i + 1][j + 1] = p_sum[i][j + 1] + p_sum[i + 1][j] - p_sum[i][j] + num;
		}
	}

    // 구해야 하는 구간을 입력받고 구간합 출력하기
	for (int i = 0; i < M; i++) {
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;

		cout << p_sum[y2][x2] - p_sum[y1 - 1][x2] - p_sum[y2][x1 - 1] + p_sum[y1 - 1][x1 - 1] << '\n';

	}

	return 0;
}