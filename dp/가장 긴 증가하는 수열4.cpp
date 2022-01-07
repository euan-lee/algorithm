#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int main() {
	int dp[1000];
	int num[1000];
	int n;
	cin >> n;
	int ans = 0;
    stack <int> s;
    int a;
    int idx = 1;
    for(int i=0;i<n;i++){
        cin>>a;
        num[i]=a;
        int tmp=0;
        for(int j=0;j<i;j++){
            if(num[j]<num[i] && dp[j]>tmp) tmp=dp[j];
        }
        dp[i]=tmp+1;
        if(ans<dp[i]){
            ans=dp[i];
            idx=i;
        }
    }
    s.push(num[idx]);
    int curr= idx;
    for(int i=idx-1;i>=0;i--){
        if(num[i]<num[curr] && dp[i]+1==dp[curr]){
            curr=i;
            s.push(num[i]);
        }
    }
    cout<<ans<<"\n";
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
	return 0;
}