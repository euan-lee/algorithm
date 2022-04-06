#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 2100000000
#define VMAX 2001
 
using namespace std;
 
int dist[VMAX]={0};
 
void dijkstras(int start, vector<pair<int,int>> a[]){
  for(int i=0; i<VMAX; i++) dist[i]=INF;
  dist[start]=0;
  priority_queue<pair<int,int>> pq;
  pq.push({-0, start});
  while(!pq.empty()){
    int x = pq.top().second;
    int wx = -pq.top().first;
    pq.pop();
    for(int i=0; i<a[x].size(); i++){
      int y = a[x][i].first;
      int wy = a[x][i].second;
      if(dist[y] > dist[x] + wy){
        dist[y] = dist[x] +wy;
        pq.push({-dist[y], y});
      }
    }
  }
}
int main(){
  int T; cin >> T;
  for(int k=0; k<T; k++){
    int n,m,t; cin >> n >> m >> t; // 교차로, 도로, 목적지 후보
    int s,g,h; cin >> s>> g >> h; // 출발지, g과h 사이의 도로
    
    vector<pair<int,int>> a[VMAX];
    vector<int> dst;
    int init[VMAX]={0};
    int hdist[VMAX]={0};
    int gdist[VMAX]={0};
    vector<int> res;
    int gh=0, hg=0;
    int sg=0,sh=0;
 
    for(int x,y,w,i=0; i<m; i++){
      scanf("%d %d %d", &x, &y, &w);
      a[x].push_back({y,w});
      a[y].push_back({x,w});
    }
    for(int x,i=0; i<t; i++){
      scanf("%d", &x);
      dst.push_back(x);
    }
    for(int i=0; i<a[g].size(); i++)
      if(a[g][i].first == h){
        gh = a[g][i].second;
        hg = a[g][i].second;
      }
    dijkstras(s,a);
    for(int i=1; i<=n; i++) init[i] = dist[i];
    sg = dist[g];
    sh = dist[h];
 
    dijkstras(h,a);
    for(int i=1; i<=n; i++) hdist[i] = dist[i];
 
    dijkstras(g,a);
    for(int i=1; i<=n; i++) gdist[i] = dist[i];
 
    for(int i=0; i<dst.size(); i++){
      int d = dst[i];
      if(init[d] == sg + gh + hdist[d]){
        res.push_back(d);
      }
      if(init[d] == sh + hg + gdist[d]){
        res.push_back(d);
      }
    }
    sort(res.begin(), res.end());
    for(int i=0; i<res.size(); i++) printf("%d ", res[i]);
    printf("\n");
  }
}
