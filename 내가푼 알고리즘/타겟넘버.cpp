#include <string>
#include <vector>

using namespace std;
int cnt;
void dfs(int answer, int n,int target,vector<int> numbers){
    
    if(n==numbers.size()){
        if(answer==target){
            cnt++;
        }
        return ;
    }
    answer=answer+numbers[n];
    n++;
    dfs(answer,n,target,numbers);
    n--;
    answer=answer-2*numbers[n];
    n++;
    dfs(answer,n,target,numbers);
    
}

int solution(vector<int> numbers, int target) {
    vector<string> op;
     cnt=0;
    dfs(0,0,target,numbers);
    printf("cnt:%d\n",cnt);
    int answer=cnt;
    return answer;
}
