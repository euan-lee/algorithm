#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int n,m;
int visit[32001];
stack <int> ans;
void dfs(vector <vector<int>> &graph ,int num){
    visit[num]=1;
    for(int i=0;i<graph[num].size();i++){
        int des = graph[num][i];
        if(visit[des]==0) dfs(graph, des);
    }
    ans.push(num);
}

void go(vector <vector<int>> &graph){
    for(int i=1;i<=n;i++){
        if(visit[i]==0) {
            dfs(graph, i);
        }
    }
}


int main(){
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>n>>m;
    vector <vector<int>> g(n+1);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
    }
    go(g);
    while(!ans.empty()){
        cout<<ans.top()<<" ";
        ans.pop();
    }
    return 0;
}
