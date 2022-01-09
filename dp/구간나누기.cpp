#include <iostream>
using namespace std;
int n, m;
bool visit[102][52];
int dp[102][52];
int sum[102]; 
int areaSum(int num, int area) {
    if(area == 0) return 0;
    if(num < 2*area-1) return -987654321; 
    if(visit[num][area]) return dp[num][area];
    visit[num][area] = true;
    dp[num][area] = areaSum(num-1, area);
    for(int i = num; i >= 1; i--) {
        dp[num][area] = max(dp[num][area], sum[num] - sum[i-1] + areaSum(i-2, area-1)); 
    } 
    return dp[num][area]; 
    }
int main() { 
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL); 
    cout.tie(NULL); cin >> n >> m;
    int seq; 
    for(int i = 1; i <= n; i++){ 
        cin >> seq;
        sum[i] = sum[i-1] + seq;
    }
    cout << areaSum(n, m); 
    return 0;
}
