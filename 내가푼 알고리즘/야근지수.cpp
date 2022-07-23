
#include <vector>
#include <queue>
using namespace std;

long long solution(int n, vector<int> works) {
    // std::priority_queue를 정의하고, works에 들어온 작업들을 옮겨담는다.
    std::priority_queue<int> q(works.begin(), works.end());
    // 작업시간 n 만큼 돌며, 작업들의 최댓값에서 1씩 뺀다.
    for (int i = 0; i < n; i++) {
        if (q.top() > 0) {
            // 큐에서 최댓값을 가져오고, -1 해서 다시 넣는다.
            int tmp = q.top();
            q.pop();
            q.push(tmp-1);
        }
    }
    // 마지막으로, 남은 작업량으로 피로도를 계산한다.
    long long answer = 0;
    while(!q.empty()) {
        answer += (long long)q.top() * (long long)q.top();
        q.pop();
    }
    return answer;
}
