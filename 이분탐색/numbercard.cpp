#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N = 0, M = 0;
	int i = 0;

	cin >> N;
	vector<int>card(N, 0);
	for (i = 0; i < N; ++i)
		cin >> card[i];
	sort(card.begin(), card.end());

	cin >> M;

	vector<int>check(M, 0);
	vector<int>answer(M, 0);

	for (i = 0; i < M; ++i) {
		cin >> check[i];
		int low = 0;
		int high = N - 1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (card[mid] == check[i]) {
				answer[i]++;
				break;
			}
			else if (card[mid] < check[i])
				low = mid + 1;
			else if (card[mid] > check[i])
				high = mid - 1;
		}
	}
	for (i = 0; i < M; ++i)
		cout << answer[i] << " ";
}