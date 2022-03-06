#include <iostream>
#include <vector>
using namespace std;

bool visited[11][11];
int arr[11][11];
int n, m, k;
int ans =  -40000;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void backtrack(int px, int py, int cnt, int sum){
	if(cnt == k){ //재귀 종료 조건
		ans = max(ans, sum);
		return;
	}
	for(int x=px; x<n; x++){
		for(int y=(x == px ? py : 0); y<m; y++){
			if(!visited[x][y]){
				bool flag = true;
				for(int i=0; i<4; i++){ //인접 여부 판단
					int nx = x + dx[i];
					int ny = y + dy[i];
					if(0 <= nx && nx < n && 0 <= ny && ny < m){ //범위 내에 존재 -> 선택 가능한 경우
						if(visited[nx][ny])	flag = false; //이미 방문한 칸이면 선택 불가
					}
				}
				if(flag){
					visited[x][y] = true;
					backtrack(x, y, cnt + 1, sum + arr[x][y]);
					visited[x][y] = false;
				}
			}
		}
	}

}

int main(){
	cin>>n>>m>>k;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cin>>arr[i][j];
	}
	backtrack(0, 0, 0, 0);
	cout<<ans<<'\n';
	return 0;
}
