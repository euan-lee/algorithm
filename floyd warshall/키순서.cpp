#include <iostream>
#define INF 1000000000
using namespace std;
 
bool d[501][501];
int N, M, ans;
 
void solve() {
    for (int i = 1; i <= N; i++) {
        int cnt = 0;
        for (int j = 1; j <= N; j++) {
            if (d[i][j] || d[j][i]) cnt++;
        }
 
        if (cnt == N - 1) ans++;
    }
 
    cout << ans << '\n';
}
 
void func() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (d[i][k] && d[k][j]) {
                    d[i][j] = true;
                }
            }
        }
    }
}
 
void input() {
    int u, v;
    cin >> N >> M;
    while (M--) {
        cin >> u >> v;
        d[u][v] = true;
    }
}
 
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);
 
    input();
    func();
    solve();
 
 
    return 0;
}
