#include <string>
#include <vector>
using namespace std;
int arr[1000];

void Outside(int n,int start,int start_value){
    if(n<0){
        return;
    }
    arr[start]=start_value;
    printf("start:%d\n",start);
    for(int i=start+1;i<=start+n-1;i++){
        arr[i]=arr[i-1]+i;
    }
    for(int i=start+n;i<start+2*n-1;i++){
        arr[i]=arr[i-1]+1;
    }
    for(int i=start+2*n-1;i<start+n*(n+1)/2;i++){
        arr[i]=arr[i-1]-1;
    }
    for(int i=0;i<n*(n+1)/2;i++){
        printf("%d ",arr[i]);
    }
    Outside(n-3,1+3*(n-1),);
}
vector<int> solution(int n) {
    vector<int> answer;
    answer.push_back(0);
    arr[1000]={0,};
    //arr[n]은 n+1이 배열의 어느 위치에 있는지?이다.
    Outside(n,0);
    return answer;
}
