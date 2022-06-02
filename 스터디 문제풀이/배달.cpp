#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int roads[51][51];
int dp[51];
void dijkstra(int start,int N){
    dp[1]=0;

    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,1});

    while(!pq.empty()){
       int current= pq.top().second;
       int time = pq.top().first;
        pq.pop();
        if(dp[current]<time)
            continue;

        for(int i=0; i<=N;i++){
            if(roads[current][i]!=0){
                int next = i;
                int nextTime = time+ roads[current][i];
                if(dp[next]>nextTime){
                    dp[next] = nextTime;
                    pq.push({nextTime,next});
                }
            }
        }

    }
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    for(int i=0; i<road.size();i++){
        int r =road[i][0], c =road[i][1], cost = road[i][2];
            if(roads[r][c]==0){
            roads[r][c] =cost;
            roads[c][r] =cost;
            }
            else{
                roads[r][c] = min(roads[r][c],cost);
                roads[c][r] = min(roads[c][r],cost);
            }
    }

    for(int i=0; i<51;i++){
        dp[i]= 987654321;
    }
    dijkstra(1,N);


    for(int i=1; i<=N;i++){
        if(dp[i]<=K){
            answer++;

        }
    }


    return answer;
}
