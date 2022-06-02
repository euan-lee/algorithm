#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int> pq(works.begin(),works.end());
    while(n > 0)
    {
        if(pq.top() > 0)
        {
            int temp = pq.top();
            pq.pop();
            pq.push(temp - 1);
            n--;
        }
        else
        {
            break;
        }
    }
    while(!pq.empty())
    {
        int temp = pq.top();
        answer += temp * temp;
        pq.pop();
    }
    return answer;
}
