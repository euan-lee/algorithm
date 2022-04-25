#include <iostream>
#include <vector>
using namespace std;
#define RC_MX 100 + 2
// global 
#pragma warning(disable:4996)
#define SIDE 4
int side_arr[SIDE][2] = { { 1,0 },{ 0,-1 },{ -1,0 },{ 0,1 } };
 
// 드래곤 커브를 만드는 메소드 
void make_dragon_curve(vector<pair<int, int>>& _dragon_curve, int _gene) {
    int make_num = _gene;
    while (make_num--) {
        int dragon_size = _dragon_curve.size();
        // 가장 마지막 점이 회전의 기준 
        pair<int, int> pivot = _dragon_curve.back();
        for (int dra_idx = dragon_size - 2; dra_idx >= 0; dra_idx--) {
            // 원점이동 -> 회전이동 -> 다시 이동 후에 삽입한다. 
            pair<int, int> new_pivot = { _dragon_curve[dra_idx].first - pivot.first,
                _dragon_curve[dra_idx].second - pivot.second };
            _dragon_curve.push_back({ -new_pivot.second + pivot.first, new_pivot.first + pivot.second });
        }
    }
}
 
int main() {
    int is_visited[RC_MX][RC_MX] = { 0 };
    int N; scanf("%d", &N);
    for (int n_idx = 0; n_idx < N; n_idx++) {
        int x, y, d, g; scanf("%d %d %d %d", &x, &y, &d, &g);
        // 드래곤 커브를 만든다. 벡터로 표현한다
        vector<pair<int, int>> dragon_curve;
        dragon_curve.push_back({ x,y });
        dragon_curve.push_back({ x + side_arr[d][0], y + side_arr[d][1] });
 
        make_dragon_curve(dragon_curve, g);
        // 드래곤 커브가 도달할 수 있는 배열에 전부 표시한다. 
        for (auto dot : dragon_curve)
            is_visited[dot.second][dot.first] = 1;
    }
    int answer = 0;
    for (int x_idx = 0; x_idx < RC_MX; x_idx++)
        for (int y_idx = 0; y_idx < RC_MX; y_idx++)
            // 4 사이드 전부 도달한 곳이면 ++ 
            if (is_visited[x_idx][y_idx] && is_visited[x_idx][y_idx + 1] 
              && is_visited[x_idx + 1][y_idx] && is_visited[x_idx + 1][y_idx + 1]) 
                answer++;
 
    printf("%d", answer);    return 0;
}
