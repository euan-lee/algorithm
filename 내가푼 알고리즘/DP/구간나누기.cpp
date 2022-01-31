#include <iostream>
#include <algorithm>
#define INF 1000000000
using namespace std;
 
int list[101], sum[101], dp[101][51];
int N, M;
 
int func(int idx, int cnt) {
    if (cnt == M) return 0;
    if ((N - idx + 2) / 2 < M - cnt) return -INF;
 
    int &ret = dp[idx][cnt];
    if (ret != -INF) return ret;
    ret = func(idx + 1, cnt);
 
    for (int i = idx; i <= N; i++) {
        ret = max(ret, func(i + 2, cnt + 1) + sum[i] - sum[idx - 1]);
    }
 
    return ret;
}
 
void init() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = -INF;
        }
    }
}
 
void input() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> list[i];
        sum[i] = sum[i - 1] + list[i];
    }
    init();
}
 
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);
 
    input();
    cout << func(1, 0) << '\n';
 
    return 0;
}
