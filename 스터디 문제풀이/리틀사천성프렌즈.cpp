#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct qinfo{
//행, 열, 방향, 꺾은 횟수
    int x,y,dir,cnt;
};
typedef struct ainfo{
    int x,y;
};

int pairCnt = 0;
int N = 0,M = 0;

bool inRange(int x, int y){
    return (0 <= x && x < M && 0 <= y && y < N);
}

bool BFS(int start_x, int start_y, int end_x, int end_y, vector<string> &boards){
    
    pair<int, int> nextdir[4] = {{1,0},{0,1},{-1,0},{0,-1}};
    
    queue<qinfo> q;
    
    //어떤 방향으로 출발해도 상관 없다는 표시로 dir = -1;
    q.push({start_x, start_y, -1, 0});
    
    while(!q.empty()){
        
        int now_x = q.front().x; int now_y = q.front().y;
        int cnt = q.front().cnt; int dir = q.front().dir;
        q.pop();
        
        for(int i=0;i<4;i++){
            
            //dir이 -1이 아닐 때 역 방향이라면 continue
            if(dir != -1 && abs(dir - i) == 2)
                continue;
            
            int next_x = now_x + nextdir[i].first;
            int next_y = now_y + nextdir[i].second;
            int next_cnt = (dir == i || dir == -1) ? cnt:cnt+1; //방향이 다르다면 꺾어야만 함
            
            if(inRange(next_x, next_y)){
                //어디로 가던지 꺾은 횟수가 1번 이하여야 함
                if(next_cnt <= 1){
                    if(boards[next_x][next_y] == '*'){
                        continue;
                    }
                    else if(boards[next_x][next_y] == '.'){
                        q.push({next_x, next_y, i, next_cnt});
                    }
                    else {
                        //제거 할 수 있는 패를 찾았다면
                        if(next_x == end_x && next_y == end_y)
                            return true;
                    }    
                }
            }
        }
    }
    return false;
}

string solve(vector<vector<ainfo>> &arr, vector<string> &boards){
    
    string ans = "";
    bool flag = true;
    
    while(flag){
        
        flag = false;
        
        //2번 과정, A~Z까지 검사
        for(int i=0;i<arr.size();i++){
            //해결 해야할 요소가 있다면
            if(arr[i].size() > 1){
            	//BFS를 통해 제거 가능한 짝이 있는지 검사
                if(BFS(arr[i][0].x, arr[i][0].y, arr[i][1].x, arr[i][1].y, boards)){
                	//3번 과정, 제거한 부분을 빈 공간으로 변경
                    boards[arr[i][0].x][arr[i][0].y] = boards[arr[i][1].x][arr[i][1].y] = '.'; //빈칸으로 만듬
                    arr[i].clear(); //배열 정보 삭제
                    pairCnt -= 2; //제거 해야할 짝의 수 감소
                    ans += char(i + int('A')); 
                    flag = true;
                    break;
                }    
            }
        }   
    }
    
    //4번 과정
    if(pairCnt == 0) //모든 짝을 제거한 경우
        return ans;
    else //더 이상 해결을 못하는 경우
        return "IMPOSSIBLE";
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    
    string answer = "";
    vector<vector<ainfo>> arr(26, vector<ainfo>());
    
    //전역 변수 초기화
    pairCnt = 0;
    M=m; N=n;
    
    //1번 과정, 모든 짝의 위치를 저장
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if('A' <= board[i][j] && board[i][j] <= 'Z'){
            	//alphabet을 int로 변환 후 위치 저장
                arr[int(board[i][j]) - int('A')].push_back({i,j});
                pairCnt++; //제거 해야 할 짝의 수 증가
            }
        }
    }
                
    return answer = solve(arr,board);
}
