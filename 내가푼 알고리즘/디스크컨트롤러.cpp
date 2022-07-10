#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

bool cmp (vector<int> a , vector<int> b){
    if(a[0]==b[0]) return a[1]<b[1];
    return a[0]<b[0];
}

int solution(vector<vector<int>> jobs) {

    sort(jobs.begin(),jobs.end(),cmp);
    int current=jobs[0][0]+jobs[0][1];
    int answer = jobs[0][1];
    //current보다 작은 경우인 것들만 크기 작은 순으로 비교

    for(int i=1; i<jobs.size();i++){

        priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,greater<pair<pair<int,int>,int>>> pq;
        for(int j=i; j<jobs.size();j++){//대기시간이 current보다 작은 것들 추출
            if(current>=jobs[j][0]&&jobs[j][0]>=0)
                pq.push({{jobs[j][1],jobs[j][0]},j});
                //pq.top().first.first는 소요 시간 first.second는 요청 시간
                //second는 인덱스
                //소요 시간 적은 것부터 오름차순 
            else 
                continue;
        }
        if(!pq.empty()){//현재 작업을 수행하고 있는 경우
            current += pq.top().first.first;
            answer += current-pq.top().first.second;
            jobs[pq.top().second][0]=-1;//수행한 작업은 -1로 탐색에서 제외시키기
            i--;//최상위 for문에서 i가 증가하여 현재 작업이 스킵되는 것을 방지
        }
        else if(jobs[i][0]>=0){//현재 작업을 수행하고 있지 않은 경우
            current = jobs[i][0]+jobs[i][1];
            answer +=jobs[i][1]; 
        }
    }

    return answer/jobs.size();
}
