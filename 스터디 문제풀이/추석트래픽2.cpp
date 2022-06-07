
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <queue>
#include <math.h>

using namespace std;

double end_t[2001];
double start_t[2001];
double work_t[2001]; // 실행 시간

void make_end(string s, int pos){ // 시작 시간,분,초,걸리는 시간
    double end_c = stod(s.substr(11,2)) * (double)3600.0;
    double end_m = stod(s.substr(14,2)) * (double) 60.0;
    double end_s = stod(s.substr(17,6));
    string temp = "";
    for(int i=24;i<s.size()-1;i++){
        temp.push_back(s[i]);
    }
    work_t[pos] = stod(temp);
    end_t[pos] = end_c+end_m+end_s;
}

void make_start(int pos){ // 끝나는 시간,분,초
    start_t[pos] = end_t[pos] - work_t[pos] + (double)0.001;
}

bool cmp (int a, int b){
   if(start_t[a] != start_t[b]) return start_t[a] < start_t[b];
    else if(end_t[a] != end_t[b]) return end_t[a] < end_t[b];
    else return a<b;
}



int solution(vector<string> lines) {
    int answer = 1;
    vector<int> v;
    for(int i=0;i<lines.size();i++){
        v.push_back(i);
        make_end(lines[i],i);
        make_start(i);
    }
    sort(v.begin(),v.end(),cmp);

    priority_queue<double> q;
    q.push(-end_t[v[0]]);


    for(int i=1;i<v.size();i++){ //start - end > 이면 계속 pop, 마지막에 push
        int next = v[i];
        while(!q.empty()){
            if(start_t[next] + q.top() >= (double)1) q.pop();
            else break;
        }
        q.push(-end_t[next]);
        answer = max(answer,(int)q.size());
    }

    return answer;
}
