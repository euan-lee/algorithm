#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int N,M;
vector<vector<int> > adj;


vector<bool> visited;
vector<int> order;
void dfs(int here) {
	visited[here] = true;
	
	for (int there = 0; there < adj.size(); there++) {
		if (adj[here][there] && !visited[there])
			dfs(there);
	}
	//위의 정점이 다 종료된 후에 이 곳의 정점(here)이 추가가 되어야함
	order.push_back(here);
}


void topologicalSort() {
	int n = adj.size();
	visited = vector<bool>(N, false);

	order.clear();

	//들어오는 간선이 없을 경우가 있을 수 있으므로 모두 DFS 탐색
	for (int i = 0;i<N;i++)
		if (!visited[i]) dfs(i);

	//종료된 순서를 거꾸로 만든다.
	reverse(order.begin(), order.end());
}

void printOrder() {
	for (int i = 0; i < order.size(); i++)
		printf("%c ", order[i] + 'A');
	printf("\n");
}
int main() {
	printf("정점의 갯수 : ");
	scanf("%d", &N);
	
	printf("간선의 갯수 : ");
	scanf("%d", &M);

	visited = vector<bool>(N, false);
	adj = vector<vector<int>>(N, vector<int>(N, 0));

	for (int i = 0; i < M; i++) {
		char from, to;
		printf("정점1 -> 정점2 : ");
		scanf(" %c %c", &from, &to);
		adj[from-'A'][to-'A'] = 1;
	}
	
	topologicalSort();
	printOrder();
}

//dfs
