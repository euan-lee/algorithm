#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> v_map;
bool visited[11][11];
int n, m, k;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int max_val = -99999999;

void input() {
	cin >> n >> m >> k;
	v_map.resize(n, vector<int>(m));
	for (int i = 0;i < n;++i) {
		for (int j = 0;j < m;++j) {
			cin >> v_map[i][j];
		}
	}
}
bool no_injub(int x, int y) {
	for (int i = 0;i < 4;++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
			if (visited[nx][ny] == true) {
				return false;
			}
		}
	}
	return true;
}
void sol(int sum, int cnt) {
	if (cnt == k) {
		if (max_val < sum) {
			max_val = sum;
		}
		return;
	}

	for (int i = 0;i < n;++i) {
		for (int j = 0;j < m;++j) {
			if (visited[i][j] == false && no_injub(i, j) == true) {
				visited[i][j] = true;
				sol(sum + v_map[i][j], cnt + 1);
				visited[i][j] = false;
			}
		}
	}
}

int main() {
	input();
	sol(0, 0);
	cout << max_val;
}
