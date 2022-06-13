#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int start=0;
    int end=1;
    int cnt=0;
    int sum;
    vector<int> sue;
    
    for(int i=1;i<=n;i++){
        sue.push_back(i);
    }
    
    while(start!=end){
        sum=0;
        for(int i=start;i<end;i++){
            sum=sum+sue[i];
        }
        if(sum<n){
            end++;
        }
        else if(sum==n){
            cnt++;
            start++;
            continue;
        }
        else{
            start++;   
        }   
    }
    int answer =cnt;
    return answer;
}
