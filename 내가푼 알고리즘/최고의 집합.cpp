
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    if(n > s){
        answer.emplace_back(-1);
        return answer;
    }
    int quo = s / n;
    int rem = s % n;
    int num = 0;
    
    if(s % n != 0) num = 1; //나누어 떨어지지 않는다면 나머지를 1씩 분배
    
    for(int i = 0; i < n; i++)
        if(i >= n - rem) answer.emplace_back(quo + 1);
        else answer.emplace_back(quo);
    
    return answer;
}
