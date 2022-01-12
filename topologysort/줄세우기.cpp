#include<stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

int indegree[32001];
vector<int> v[32001];

int main() {
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		indegree[b]++;
		v[a].push_back(b);
	}

	queue<int> now;
	for (int i = 1; i <= n; i++)
		if (indegree[i] == 0) now.push(i);

	while(!now.empty())	{
		int i = now.front(); now.pop();
		printf("%d ", i);

		for(int j=0;j<v[i].size();j++)
			if (--indegree[v[i][j]] == 0)
				now.push(v[i][j]);
	}
}