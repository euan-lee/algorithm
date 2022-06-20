#include <string>
#include <vector>
using namespace std;

long long solution(int n) {
    long long answer = 0;
    int arr[2000]={0,};
    arr[2]=2;
    arr[1]=1;
    for(int i=1;i<n-1;i++){
        arr[i+2]=(arr[i+1]+arr[i])% 1234567;
    }
    printf("%d",arr[n]);
    answer=arr[n];
    return answer;
}
