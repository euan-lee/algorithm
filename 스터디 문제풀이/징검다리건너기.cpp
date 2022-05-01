#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// m번째 인원이 건널 수 있는지 확인
bool can_move(vector<int>& stones, int k, int m) {
    int cnt = 0;
    for (int i = 0; i < stones.size(); i++) {
        if (stones[i] - m <= 0) cnt++;
        else cnt = 0;
        if (cnt == k) return false;
    }
    return true;
}

int solution(vector<int> stones, int k) {
    int size = stones.size();
    int left = 1;
    int right = *max_element(stones.begin(), stones.end());

    while (left <= right) {
        int mid = (left + right) / 2;

        if (can_move(stones, k, mid)) left = mid + 1;
        else right = mid - 1;
    }
    int answer = left;
    return answer;
}



