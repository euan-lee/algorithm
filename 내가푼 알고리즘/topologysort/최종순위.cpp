
#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <vector> 
#include <queue> 
#include <stack>
#include <fstream> 
#include <string> 
#include <algorithm>

using namespace std;

int testcase;
int N, M;
bool adj[501][501];
int score[501];
int result[501];
int inDegree[501];

int main() {
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &score[i]);
			score[i]--;
			result[i] = -1;
			inDegree[i] = 0;
			for (int j = 0; j < N; j++) {
				adj[i][j] = false;
			}
		}

		for (int i = 0; i < N; i++) {
			int start = score[i];
			for (int j = i + 1 ; j < N; j++) {
				adj[start][score[j]] = true;
				inDegree[score[j]]++;
			}
		}

		scanf("%d", &M);

		for (int i = 0; i < M; i++) {
			int from, to;
			scanf("%d %d", &from, &to);
			from--;
			to--;
			if (adj[from][to]) {
				adj[from][to] = false;
				adj[to][from] = true;
				inDegree[to]--;
				inDegree[from]++;
			}
			else {
				adj[to][from] = false;
				adj[from][to] = true;
				inDegree[from]--;
				inDegree[to]++;
			}
		}
		
		queue<int> resultQ;
		for (int i = 0; i < N; i++) {
			if(inDegree[i] == 0) resultQ.push(i);
		}

		for (int loop = 0; loop < N; loop++) {
			if (resultQ.empty()) {
				cout << "IMPOSSIBLE" << endl;
				goto ENDLOOP;
			}
			if (resultQ.size() > 1) {
				cout << "?" << endl;
				goto ENDLOOP;
			}
			int now = resultQ.front();
			result[loop] = now;
			resultQ.pop();
			inDegree[now]--;
			for (int i = 0; i < N; i++) {
				if (adj[now][i]) inDegree[i]--;
				if (inDegree[i] == 0) resultQ.push(i);
			}
		}

		for (int i = 0; i < N; i++) {
			cout << result[i] + 1 << " ";
		}
		cout << endl;

	ENDLOOP:;

	}


	return 0;
}
