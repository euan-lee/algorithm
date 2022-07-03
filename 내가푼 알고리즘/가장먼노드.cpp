#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[20001];
int visited[20001];
int answer;
int level_store[20001]; 

void Bfs(int root){
        int level=0;
        queue<pair<int,int>> q;
        visited[root]=1;
        level_store[level]=1;
        q.push(make_pair(root,level));
        while(q.empty()==0){
            root=q.front().first;
            level=q.front().second+1;
            for(int i=0;i<graph[root].size();i++){
                if(visited[graph[root][i]]==0){
                    visited[graph[root][i]]=1;
                    q.push(make_pair(graph[root][i],level));   
                    level_store[level]=level_store[level]+1;
                }
            }
            q.pop();
        }
    };


int solution(int n, vector<vector<int>> edge) {
    answer = 0;
    fill_n(visited,20001,0);
    fill_n(level_store,20001,0);
    //행렬로 구현시 4억 
    //인접리스트로 구현시 7만 
    for(int i=0;i<edge.size();i++){
            graph[edge[i][0]].push_back(edge[i][1]);
            graph[edge[i][1]].push_back(edge[i][0]);
        }
    //bfs
    Bfs(1);
    //이진탐색으로 0~20000까지 탐색
  
    for(int i=0;i<20001;i++){
        printf("%d",level_store[i]);
    //    answer=max(answer,level_store[i]);
        if(level_store[i]==0){
            answer=level_store[i-1];
            break;
        }
    }
    return answer;
}
