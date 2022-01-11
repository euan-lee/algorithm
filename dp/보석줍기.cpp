#include <bits/stdc++.h>
     
using namespace std;
 
int ar[100001];
int prefix[100001];
int n, m;
int res;
 
int main()
{
    cin.tie(0); ios::sync_with_stdio(false);
    cin >> n >> m;
 
    for (int i = 1; i <= n; ++i)
    {
        cin >> ar[i];
        prefix[i] = prefix[i - 1] + ar[i];
    }
 
    int val = 0;
 
    for (int i = m; i <= n; ++i)
        res = max(res, prefix[i] - (val = min(prefix[i - m], val)));
 
    cout << res;
}
