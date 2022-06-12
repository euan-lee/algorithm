#include <string>
#include <vector>
#include <queue>
using namespace std;


int solution(vector<int> priorities, int location) {
    int x=0;
    int y=0;
    int z=0;
    int answer=0;
    priority_queue<int> pq;
    queue<pair<int,int>> q;
    for(int i=0;i<priorities.size();i++){
        pq.push(priorities[i]);
        q.push({priorities[i],i});
    }
  
    
    //여기부터 logic 보기
    while(!q.empty()){
        x=q.front().first;//우선순위
        y=q.front().second;//배열 넘버
        z=pq.top();
        if(x==z){
            pq.pop();
            q.pop();
            answer++;
            if(location==y){
                return answer; 
            }
        }
        if(x!=z){
            q.pop();  
            q.push({x,y});    
        }
      }
}
