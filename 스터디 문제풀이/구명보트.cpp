#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    sort(people.begin(), people.end());
    int answer = 0, idx = 0;
    while(people.size() > idx){
        int back = people.back(); people.pop_back();
        if(people[idx] + back <= limit){ answer++; idx++; }
        else answer++;
    }
    return answer;
}
