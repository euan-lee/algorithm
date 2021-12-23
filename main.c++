#include <iostream>
using namespace std;
#define MAX_SIZE 25
#include <queue>
#include <algorithm>

int n;
int arr[200][200]={0,};
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int col=0;
int row=0;
int house_number = 0;
bool visited[MAX_SIZE][MAX_SIZE];
int num_of_houses[MAX_SIZE * MAX_SIZE] = { 0, };
    void bfs(int y, int x)
    {
        queue< pair<int, int> > q;
        visited[y][x] = true;
        while(!q.empty()){
            y=q.front().first;
            x=q.front().second;
            q.pop();
            for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(!(0 <= nx && nx < n&& 0 <= ny && ny < n)){
                 if (arr[ny][nx] == 1 && visited[ny][nx] == false) {
                    visited[ny][nx] = true;
 
            
                    num_of_houses[house_number]++;
 
                    // 큐에 현재 nx,ny를 추가
                    q.push(make_pair(ny, nx));
                }
            }
            }
        }
        cout<<"hello";
    }
    





int main (){
  
 
    cin >> n;
    cout <<"it is "<<n;
    for(col=0;col<n;col++){
        for(row=0;row<n;row++){
            cin >> arr[col][row];
        }
    }

    sort(num_of_houses + 1, num_of_houses + house_number + 1);
   for (int i = 1; i <= house_number; i++) {
        printf("%d\n", num_of_houses[i]);
    }
    printf("%d\n", house_number);
}
