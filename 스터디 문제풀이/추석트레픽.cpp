#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

// 처리시간은 시작시간과 끝시간을 포함
// lines는 응답완료시간 S를 기준으로 오름차순 정렬
int solution(vector<string> lines) {
    int answer = 0;
    int tps = 0; // tps 최대값 비교를 위한 변수
    vector<pair<double, double>> response; // 응답시작시간, 응답완료시간

    for(auto x : lines) {
        string ss = x.substr(11,12);
        double responseCompleteTime = (stod(ss.substr(0,2)) * 3600) + (stod(ss.substr(3,2)) * 60) + stod(ss.substr(6,2)) + (stod(ss.substr(9)) / 1000.0); // 응답완료시간

        string temp = x.substr(24);
        double throughputTime = stod(temp.substr(0, temp.length()-1)); // 처리시간

        double responseStartTime = responseCompleteTime - throughputTime + 0.001;

        response.push_back(make_pair(responseStartTime, responseCompleteTime));

    }

    for(int i = 0; i < response.size(); i++) {
        double start = response[i].first;
        double end = response[i].second;
        tps = 1;

        for(int j = i + 1; j < response.size(); j++) {
            if(start+1 >= response[j].first || end+1 > response[j].first) {

                    tps++;
            }

        }

        answer = max(answer, tps);
    }

    return answer;
}
