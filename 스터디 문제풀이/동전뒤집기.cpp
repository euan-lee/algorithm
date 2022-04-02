#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <cmath>
#define endl '\n'

using namespace std;

int n;
string str[20];
int dp[1048576];

int countT(){
  int ret = 0;
  for (int i=0; i<n; i++){
    int cnt = 0;
    for (int j=0; j<n; j++)
      if (str[j][i] == 'T')
        cnt++;
    // T가 더 많으면 뒤집은 결과 저장
    ret += min(cnt, n-cnt);
  }

  return ret;
}

void reverse(int line){
  for (int i=0; i<n; i++){
    if (str[line][i] == 'T') str[line][i] = 'H';
    else str[line][i] = 'T';
  }
}

int solve(int check){
  
  int &ret = dp[check];
  if (ret != -1) return ret;

  ret = countT();
  
  for (int next=0; next<n; next++){
    ret = min(ret, solve(check));
  }

  for (int next=0; next<n; next++){
    reverse(next);
    ret = min(ret, solve(check|(1<<next)));
    reverse(next);
  }

  return ret;
}

int main(){
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);

  cout.tie(NULL);

  // ifstream cin;
  // cin.open("input.txt");

  cin >> n;

  for (int i=0; i<n; i++){
    cin >> str[i];
  }

  memset(dp,-1,sizeof(dp));

  cout << solve(0);
}
