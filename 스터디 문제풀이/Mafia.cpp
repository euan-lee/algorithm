#include<iostream>
#include<memory.h>
#include<vector>
using namespace std;
const int MAX = 18;
 
int n;
int score[MAX];
int check[MAX];
int arr[MAX][MAX];
int en;
 
int ans = 0;
 
int findKill() {
    int maximum = 0;
    int idx;
    for (int i = 0; i < n; i++) {
        if (score[i] > maximum && check[i]==0) {
            maximum = score[i];
            idx = i;
        }
    }
    return idx;
}
 
void dfs(int man, int day) {
    if (check[en] == 1 || man == 1) {
        if (day > ans) ans = day;
        return;
    }
 
    //밤일경우
    if (man % 2 == 0) {
        for (int i = 0; i < n; i++) {
            if (i == en || check[i] == 1) continue;
 
            check[i] = 1;
            for (int j = 0; j < n; j++) {
                if(check[j]==0) score[j] += arr[i][j];
            }
            dfs(man - 1, day + 1);
 
            for (int j = 0; j < n; j++) {
                if (check[j] == 0) score[j] -= arr[i][j];
            }
            check[i] = 0;
            
        }
    }
    //낮일경우
    else {
        // 점수가 가장 높은 사람 죽이기.
        int kill = findKill();
        if (kill == en) {
            if (day > ans) ans = day;
            return;
        }
        check[kill] = 1;
        dfs(man - 1, day);
        check[kill] = 0;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
 
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> score[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    cin >> en;
 
    dfs(n, 0);
 
    cout << ans << "\n";
 
 
    return 0;
}
 
 
