#include <string>
#include <vector>
using namespace std;
int zero;
int one;
vector<vector<int>> MAP;

bool Check(int x,int y,int n){
    int prev=MAP[x][y];
    for(int i=x;i<x+n;i++){
        for(int j=y;j<y+n;j++){
            if(MAP[i][j]!=prev){
                return false;
            }    
                prev=MAP[i][j];
        }   
    }
    return true;
}
void Go(int x,int y,int n){
    if(n==0){
      return ;
    }
    if(Check(x,y,n)){
        if(MAP[x][y]==1){
            one++;
        }
        else{
            zero++;
        }
        return;
    }
    //전체 check
    Go(x+n/2,y,n/2);    
    Go(x,y+n/2,n/2);    
    Go(x,y,n/2);    
    Go(x+n/2,y+n/2,n/2);    
}

vector<int> solution(vector<vector<int>> arr) {
    zero=0;
    one=0;
    MAP = arr;
    vector<int> answer;
    Go(0,0,arr.size());
    answer.push_back(zero);
    answer.push_back(one);
    return answer;
}
