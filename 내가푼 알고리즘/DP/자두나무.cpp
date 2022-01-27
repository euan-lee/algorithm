#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int T, W;
    scanf("%d %d", &T, &W);

    int a[1001];
    for (int i = 1; i <= T; i++){
        scanf("%d", &a[i]);
    }

    int dp[1001][31][3] = { 0 };
    if (a[1] == 1) dp[1][0][1] = 1;
    if (a[1] == 2) dp[1][1][2] = 1;

    for (int i = 2; i <= T; i++){
        for (int j = 0; j <= W; j++){
            if (a[i] == 1){
                if (j == 0){
                    dp[i][0][1] = dp[i - 1][0][1] + 1;
                    continue;
                }
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][2]) + 1;
                dp[i][j][2] = dp[i - 1][j][2];
            }
            if (a[i] == 2){
                if (j == 0){
                    dp[i][0][1] = dp[i - 1][0][1];
                    continue;
                }
                dp[i][j][1] = dp[i - 1][j][1];
                dp[i][j][2] = max(dp[i - 1][j - 1][1], dp[i - 1][j][2]) + 1;
            }
        }
    }

    int ans = -1;
    for (int i = 0; i <= W; i++){
        ans = max(ans, max(dp[T][i][1], dp[T][i][2]));
    }

    printf("%d", ans);

    return 0;
}
