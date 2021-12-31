#include <iostream>
#include <cmath>
using namespace std;
int arr[20][20];
bool visited[20];
int n;
int ans = 1234567890;
void combi(int cnt, int cur){
    if(cnt == n/2){
        int a = 0;
        int b = 0;
        // check 
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if(visited[i] && visited[j]){
                    a+= arr[i][j];
                    a+= arr[j][i];
                }else if(!visited[i] && !visited[j]){
                    b+= arr[i][j];
                    b+= arr[j][i];
                }
            }
        }
        ans = min(ans, abs(a-b));
    }
  
    for(int i=0; i<n; i++){
        if(visited[i]==false && i>cur){
            visited[i] = true;
            combi(cnt+1, i);
            visited[i] = false;
        }
    }
 
}
 
 
int main(){
    cin>>n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>> arr[i][j];
        }
    }
    combi(0,-1);
    cout <<ans<<endl;
 
}
