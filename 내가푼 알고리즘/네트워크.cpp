#include <string>
#include <vector>
using namespace std;

vector<int> graph[200];
int visited[200];

void Dfs(int node){
    visited[node]=1;
    for(int i=0;i<graph[node].size();i++){
        if(visited[graph[node][i]]==0){
            Dfs(graph[node][i]);
        }
    }
}


int solution(int n, vector<vector<int>> computers) {
    visited[200]={0,};
    for(int i=0;i<computers.size();i++){
        for(int j=0;j<computers[i].size();j++){
            if(computers[i][j]==1){
                if(i==j)continue;
                graph[i].push_back(j);
            }
        }
    }
    int answer = 0;
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            Dfs(i);
            answer++;
        }
    }
    return answer;
}
