#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
vector<pair<int, int>> v[10001];
bool chk[10001];
int Start, End;
int ans;
bool bfs(int Start, int Lim) {
    queue<int> q;
    chk[Start] = true;
    q.push(Start);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (node == End) {
            ans = Lim;
            return true;
        }
        for (int k = 0; k < v[node].size(); k++) {
            int next = v[node][k].first;
            int cost = v[node][k].second;
            if (cost >= Lim && !chk[next]) {
                chk[next] = true;
                q.push(next);
            }
        }
    }
    return false;
}
 
void cal(int left, int right) {
    if (left > right) return;
    int mid = (right + left) / 2;
    memset(chk, false, sizeof(chk));
    if (bfs(Start, mid)) cal(mid+1, right);
    else cal(left, mid-1);
}
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        // 인접 리스트에 저장
        v[a].push_back(make_pair(b, c));
        v[b].push_back(make_pair(a, c));
    }
    scanf("%d %d", &Start, &End);
    // 이분 탐색
    cal(1, 1000000000);
    printf("%d\n", ans);
}

