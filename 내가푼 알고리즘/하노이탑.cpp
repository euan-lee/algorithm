#include <string>
#include <vector>

using namespace std;

void Hanoi(int n,int from,int by,int to,vector<vector<int>>&answer){
    if(n==1){
         printf("from:%d to:%d\n",from,to);
         answer.push_back({from,to});
         return;
    }
    Hanoi(n-1,from,to,by,answer);
    printf("from:%d to:%d\n",from,to);
    answer.push_back({from,to});
    Hanoi(n-1,by,from,to,answer); 
 }


vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    Hanoi(n,1,2,3,answer);
    return answer;
}
