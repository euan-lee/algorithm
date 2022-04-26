#include <string>
#include <vector>

using namespace std;

void DFS(int point, vector<vector<int>>& computers, vector<bool>& visit, int n){
    visit[point] = true;
    for (int i = 0; i < n; i++) {
        if (!visit[i] && computers[point][i]) DFS(i, computers, visit, n);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    vector<bool> visit(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!visit[i]) {
            answer++;
            DFS(i, computers, visit, n);
        }
    }
    return answer;
}
