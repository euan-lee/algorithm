#include <iostream>
#include <vector>
#include <queue>
#define MAX 987654321
 
using namespace std;
 
int n, m;
 
int Fdist[4001];
int Wdist[2][4001]; // 걸어서 또는 뛰어서 노드 v에도 도착한 최단 시간  
 
vector<vector<pair<int, int> > > edges;
 
void Fox_dijkstra(){
    
    priority_queue<pair<int, int> > pq;
    pq.push({0, 1});
    Fdist[1] = 0;
    
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();
        
        if(Fdist[here] < cost) continue;
        
        for(int i=0; i<edges[here].size(); i++){
            int next = edges[here][i].first;
            int next_cost = cost + edges[here][i].second;
            
            if(Fdist[next] > next_cost){
                Fdist[next] = next_cost;
                pq.push({-next_cost, next});
            }
        }
    }
}
 
 
void Wolf_dijkstra(){
    
    priority_queue<pair<int, pair<int, int> > > pq; // dist, node, state(0: walk/ 1: run)
    pq.push({0, {1, 1}});
    
    while(!pq.empty()){
        int here = pq.top().second.first;
        int cost = -pq.top().first;
        int state = pq.top().second.second; // 현재 노드에서 다음 노드까지  걸어갈지 뛰어갈지 상태  
        pq.pop();
        
        // 현재 상태가 뛰어서 다음 노드로 간다면, 이전에 걸었다는 의미
        // 따라서 걸어서 도착한 최소 비용이 저장된 값(Wdist) VS 걸어서 도착한 비용(cost) 비교  
        if(Wdist[(state+1)%2][here] < cost) continue; 
        
        for(int i=0; i<edges[here].size(); i++){
 
            if(state==1){
                int next = edges[here][i].first;
                int next_cost = cost + edges[here][i].second/2;
                
                if(Wdist[1][next] > next_cost){
                    Wdist[1][next] = next_cost;
                    pq.push({-next_cost, {next, 0}});
                }
            }
            else if(state==0){
                int next = edges[here][i].first;
                int next_cost = cost + edges[here][i].second*2;
                
                if(Wdist[0][next] > next_cost){
                    Wdist[0][next] = next_cost;
                    pq.push({-next_cost, {next, 1}});
                }
            }
        }
    }
}
 
 
int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    edges.resize(n+1);
    
    int u, v, w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        
        edges[u].push_back({v, w*2});
        edges[v].push_back({u, w*2});
    }
    
    for(int i=1; i<=n; i++) {
        Fdist[i] = MAX;
        Wdist[0][i] = MAX;
        Wdist[1][i] = MAX;
    }
    
    Fox_dijkstra(); // Fox
    Wolf_dijkstra(); // Wolf
    
    int answer = 0;
    for(int i=2; i<=n; i++){
        if(Fdist[i] < min(Wdist[0][i], Wdist[1][i])) answer ++;
    }
    
    cout << answer << endl;
}
