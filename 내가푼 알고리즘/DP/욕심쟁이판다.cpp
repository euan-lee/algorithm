


#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int map[500][500];
int dp[500][500];
int dy[4] = { -1, 0, 1, 0};
int dx[4] = { 0, 1, 0, -1};

int dfs(int y, int x) {
    int k;

    if (dp[y][x] == -1) {
        // first
        dp[y][x] = 1;
        int temp = 0;
        for (k = 0; k < 4; k++) {
            int newy = y + dy[k];
            int newx = x + dx[k];
            if (newy >= 0 && newy < n && newx >= 0 && newx < n && map[newy][newx] > map[y][x]) {
                temp = max(temp, dfs(newy, newx));
            }
        }
        dp[y][x] += temp;
    }
    return dp[y][x];

}


int main() {

    int i, j, ans = 0;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &map[i][j]);
            dp[i][j] = -1;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ans = max(ans, dfs(i, j));
        }
    }

    printf("%d\n", ans);

    return 0;
}



   
© Sihyung You. 2021
