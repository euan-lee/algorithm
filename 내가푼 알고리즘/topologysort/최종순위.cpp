define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
 
using namespace std;
typedef pair<int, int> p;
 
//team[i] = j 에서 기존 i등의 팀 번호가 j
//order[i] = j 에서 i번 팀의 기존 등수가 j
int n, m, team[501], order[501];        
int indegree[501];
bool adj[501][501];
vector<int> answer;
 
int topological_sort() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) que.push(i);
    }
 
    while (!que.empty()) {
        if (que.size() > 1) return 0;        //불확실한 순위
        int cur = que.front();
        que.pop();
 
        answer.push_back(team[cur]);
        if (answer.size() == n) return 1;        //올바른 순위
 
        for (int i = 1; i <= n; i++) {
            if (!adj[cur][i]) continue;
            adj[cur][i] = false;
            indegree[i]--;
            if (indegree[i] == 0) que.push(i);
        }
    }
    return -1;        //순위를 정할 수 없음
}
 
void init() {
    cin >> n;
 
    answer.clear();
    memset(team, 0, sizeof(team));
    memset(order, 0, sizeof(order));
    memset(adj, 0, sizeof(adj));
    memset(indegree, 0, sizeof(indegree));
 
    for (int i = 1; i <= n; i++) {
        cin >> team[i];
        order[team[i]] = i;
    }
 
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            adj[i][j] = true;
            indegree[j]++;
        }
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(NULL);
 
    int tc, f, s;
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        init();
        cin >> m;
        for (int j = 0; j < m; j++) {
            cin >> f >> s;
            //f를 기존 앞순위, s를 기존 뒷순위로 둠
            if (order[f] > order[s]) swap(f, s);
            //뒷순위가 앞으로 오게 되었으므로, 두 팀의 간선을 뒤집는다.
            //원래는 f -> s로 가는 간선을 s -> f로 변환
            int node_f = order[f], node_s = order[s];
 
            adj[node_f][node_s] = false;
            indegree[node_s]--;
 
            adj[node_s][node_f] = true;
            indegree[node_f]++;
        }
        int result = topological_sort();
        if (result == -1) printf("IMPOSSIBLE\n");
        else if (result == 0) printf("?\n");
        else {
            for (int j = 0; j < answer.size(); j++) printf("%d ", answer[j]);
            printf("\n");
        }
    }
 
    return 0;
}
