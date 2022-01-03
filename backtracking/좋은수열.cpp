#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>
#define MAX 80
#define INF 987654321
using namespace std;

int n;
vector<int> v;

// 좋은 수열인지 확인하는 함수
bool is_goodPermutation(){
    int len = (int) v.size();
    
    // i = 비교할 수열의 자리수
    // 만약 길이가 4라면 1자리, 2자리 수열을 비교해야함
    for(int i=1; i<=len/2; i++){
        string s1 = "";
        string s2 = "";
        
        // i 자리 길이의 수열을 만듬
        for(int j=0; j<i; j++){
            s1 += to_string(v[len - (2*i) + j]);
            s2 += to_string(v[len - i + j]);
        }
        
        // 만약 두개의 수열이 같다면 좋은 수열이 아님
        if(s1 == s2) return false;
    }
    return true;
}

void dfs(int cnt){
    // 좋은 수열의 조건을 가진 채로 cnt == n 이라면
    if(cnt == n){
        for(int i=0; i<v.size(); i++){
            cout << v[i];
        }
        cout << "\n";
        exit(0);
    }
    
    // 1,2,3 의 숫자를 넣어보고
    // 만약 좋은 수열의 조건에 만족한다면 DFS 진행
    for(int i=1; i<=3; i++){
        v.push_back(i);
        
        if(is_goodPermutation())
            dfs(cnt+1);
            
        v.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    // cin,cout 속도향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n;
    
    dfs(0);
    return 0;
}