#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
int h, w;
int arr[501];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> h >> w;
    for(int i=0 ; i<w ; i++) {
        cin >> arr[i];
    }
    int ans=0;
    for(int i=1 ; i<w-1 ; i++) {
        int left = arr[i], right = arr[i];
        for(int j=0 ; j<i ; j++) {
            left = max(left, arr[j]);
        }
        for(int j=i+1 ; j<w ; j++) {
            right = max(right, arr[j]);
        }
        int now = min(left, right);
        ans += now-arr[i];
    }
    cout << ans << "\n";
}
