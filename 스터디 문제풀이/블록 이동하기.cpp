#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dirArray[12][4] = { { 0, 1, 0, 1 },{ 1, 0, 1, 0 },{ 0, -1, 0, -1 },{ -1, 0, -1, 0 },{ 1, 1, 0, 0 },{ 0, 0, -1, -1 },{ 0, 0, 1, -1 },{ -1, 1, 0, 0 },{ 1, 1, 0, 0 },{ 0, 0, -1, -1 },{ 1, -1, 0, 0 },{ 0, 0, -1, 1 } };
// 아 => 왼 => 위 => 오 => 가로형 => 세로형
int row;
vector<vector<int>> board;

struct Robot { // 계산 편하게 struct 정의
    int x; int y; int x2; int y2; int time;
    Robot(int a, int b, int c, int d, int e) {
        x = a; y = b; x2 = c; y2 = d; time = e;
    }
};

bool isThereOkay(int r1, int c1, int r2, int c2) {
    // 범위 및 벽 체크
    if (r1<0 || c1<0 || r2<0 || c2<0)
        return false;
    if (r1 > row || r2 > row || c1 > row || c2 > row)
        return false;
    if (board[r1][c1] == 1 || board[r2][c2] == 1)
        return false;
    return true;
}

vector<int> whereCanIGo(Robot& pos) {
    vector<int> candidate;

    for (int i = 0; i<4; i++) {
        pos.x += dirArray[i][0];
        pos.y += dirArray[i][1];
        pos.x2 += dirArray[i][0];
        pos.y2 += dirArray[i][1];
        if (isThereOkay(pos.x, pos.y, pos.x2, pos.y2)) {
            candidate.push_back(i);
            if (pos.x == pos.x2) { // 가로 배치일 때
                if (i == 1) {
                    // 아래쪽으로 이동 가능하면 4, 6번의 회전도 가능
                    candidate.push_back(4);
                    candidate.push_back(6);
                }
                if (i == 3) {
                    // 위쪽으로 이동 가능하면 5, 7번의 회전도 가능
                    candidate.push_back(5);
                    candidate.push_back(7);
                }
            }
            else if (pos.y== pos.y2) { // 세로 배치
                if (i == 0) {
                    candidate.push_back(8);
                    candidate.push_back(11);
                }
                if (i == 2) {
                    candidate.push_back(9);
                    candidate.push_back(10);
                }
            }
        }
        pos.x -= dirArray[i][0];
        pos.y -= dirArray[i][1];
        pos.x2 -= dirArray[i][0];
        pos.y2 -= dirArray[i][1];
    }
    return candidate;
}


string makeKey(int ax, int ay, int bx, int by) {
    if (ax > bx || (ax == bx && ay > by)) {
        int tmp = ax;
        int tmp2 = ay;
        ax = bx; ay = by;
        bx = tmp; by = tmp2;
    }
    return to_string(ax) + "/" + to_string(ay) + "//" + to_string(bx) + "/" + to_string(by);
}

int solution(vector<vector<int>> board2) {
    int answer = 1e8;
    board = board2; // 전역 변수로 사용
    row = board.size() - 1; // 전역 변수로 사용

    vector<string> visited;

    queue<Robot> q;
    Robot* first = new Robot(0, 0, 0, 1, 0);
    q.push(*first); // 첫 위치 저장
    visited.push_back(makeKey(0, 0, 0, 1)); // 첫 위치 방문 기록

    while (q.size()) {
        auto a = q.front(); q.pop(); // queue에 담긴 위치를 하나씩 빼면서

        if ((a.x == row && a.y == row) || (a.x2 == row && a.y2 == row)) { // 도착했을 때
            answer = a.time;
            break;
        }

        vector<int> candidate = whereCanIGo(a); // 현재 위치에서 이동할 수 있는 곳의 정보 받아오기

        while(candidate.size()){
            int idx = candidate.back(); candidate.pop_back();

            int r1 = a.x + dirArray[idx][0];
            int c1 = a.y + dirArray[idx][1];
            int r2 = a.x2 + dirArray[idx][2];
            int c2 = a.y2 + dirArray[idx][3];

            if (r1 > r2 || (r1 == r2 && c1 > c2)) { // r1, c1이 작게 유지
                int tmp = r1; int tmp2 = c1;
                r1 = r2; c1 = c2;
                r2 = tmp; c2 = tmp2;
            }

            if (find(visited.begin(), visited.end(), makeKey(r1, c1, r2, c2)) != visited.end())
                // 이미 방문했던 곳이면 뛰어넘기
                continue;

            visited.push_back(makeKey(r1, c1, r2, c2)); // 위치 방문 기록
            Robot* tmp = new Robot(r1, c1, r2, c2, a.time + 1);
            q.push(*tmp); // 다음 위치 저장
        }
    }


    return answer;
}
