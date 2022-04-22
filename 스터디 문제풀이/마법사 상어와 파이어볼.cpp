#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct fireball{
    int x;
    int y;
    int mass;
    int s;
    int d;
};
vector<fireball> map[51][51];
vector<fireball> fireballs;
bool isDir(int x, int y);
void split();
void move();
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
int N, M, K;

int main(){
    cin >> N >> M >> K;
    int x, y, mass, d, s, ans=0;
    for(int i=1; i<=M; i++){
        cin >> x >> y >> mass >> s >> d;
        fireballs.push_back({x, y, mass, s, d});
    }
    for(int i=1; i<=K; i++){
        move();
        split();
    }
    for(int i=0; i<fireballs.size(); i++) ans += fireballs[i].mass;
    cout << ans;
}

void move(){ // 파이어볼 이동
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            map[i][j].clear();
        }
    }

    for(int i=0; i<fireballs.size(); i++){
        fireball cur = fireballs[i];
        int cx = cur.x, cy = cur.y;
        int nx = cx+dx[cur.d]*cur.s, ny = cy+dy[cur.d]*cur.s;
        while(nx < 1) nx += N; // 주의!! if문 만으로는 안된다
        while(ny < 1) ny += N;
        while(nx > N) nx -= N;
        while(ny > N) ny -= N;
        map[nx][ny].push_back({nx, ny, cur.mass, cur.s, cur.d});
    }
    return;
}

void split(){
    vector<fireball> temp;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int massSum=0, sSum=0;
            if(map[i][j].size() == 0) continue;
            if(map[i][j].size() == 1) temp.push_back(map[i][j][0]); // 1개면 그대로 넣어준다.
            else { // 2개 이상일 경우 쪼갠다. 
                for(int k=0; k<map[i][j].size(); k++) {
                    massSum += map[i][j][k].mass;
                    sSum += map[i][j][k].s;
                }
                int nMass = massSum / 5;
                int nS = sSum / map[i][j].size();
                if(nMass == 0) continue;    
                if(isDir(i, j)) {
                    temp.push_back({i, j, nMass, nS, 0});
                    temp.push_back({i, j, nMass, nS, 2});
                    temp.push_back({i, j, nMass, nS, 4});
                    temp.push_back({i, j, nMass, nS, 6});
                } else {
                    temp.push_back({i, j, nMass, nS, 1});
                    temp.push_back({i, j, nMass, nS, 3});
                    temp.push_back({i, j, nMass, nS, 5});
                    temp.push_back({i, j, nMass, nS, 7});
                }
            }
        }
    }
    fireballs = temp; //fireballs 벡터를 tmp벡터로 교체한다.
}

bool isDir(int x, int y){ // 방향이 모두 홀수인지, 모두 짝수인지 판별하는 함수
    bool evenFlag=false, oddFlag=false;
    for(int i=0; i<map[x][y].size(); i++){
        if(map[x][y][i].d % 2) oddFlag = true;
        else evenFlag = true;
    }
    if(evenFlag && !oddFlag) return true;
    else if(!evenFlag && oddFlag) return true;
    else return false;
}
