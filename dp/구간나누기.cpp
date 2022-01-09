#include <bits/stdc++.h>
  
using namespace std;
 
int n, m;
int seq[101];
int prefix[101];
int dp[101][52];
 
int memo(int idx, int cnt);
 
int main() 
{
    fill(&dp[0][0], &dp[0][0] + 101 * 52, -1e9);
    cin.tie(0); ios::sync_with_stdio(false);
 
    cin >> n >> m;
 
    for (int i = 1; i <= n; ++i)
        cin >> seq[i];
 
    for (int j = 1; j <= n; ++j)
        prefix[j] = prefix[j - 1] + seq[j];
 
    cout << memo(n, m);
}
 
int memo(int idx, int cnt)
{
    if (!cnt)
        return 0;
    
    if (idx < 0 || cnt * 2 - 1 > idx)
        return -1e9;
    
    int &ret = dp[idx][cnt];
 
    if (ret != -1e9)
        return ret;
    
    ret = memo(idx - 1, cnt);
 
    for (int i = idx; i > 0; --i)
        ret = max(ret, memo(i - 2, cnt - 1) + prefix[idx] - prefix[i - 1]);
 
    return ret;
}