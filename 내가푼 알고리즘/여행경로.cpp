#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int last;
int cnt;
bool flag;

void Dfs(string way,vector<int> &visited,vector<vector<string>> &tickets,vector<string>&answer){
    if(cnt==(int)tickets.size()) flag=true;
    for(int i=0;i<tickets.size();i++){
        if(visited[i]==0&&way==tickets[i][0]){
            answer.push_back(tickets[i][1]);
            cnt++;    
            visited[i]=1;
            Dfs(tickets[i][1],visited,tickets,answer);  
            if(flag==false){
                answer.pop_back();
                visited[i]=0;
            }
        }
    }
}
vector<string> solution(vector<vector<string>> tickets) {
    flag = false;
    cnt=0;
    vector<string> answer;
    vector<int> visited;
    int index=0;
    sort(tickets.begin(), tickets.end());
    for(int i=0;i<tickets.size();i++){
        visited.push_back(0);
    }
    answer.push_back("ICN");
    Dfs("ICN",visited,tickets,answer);
    return answer;
}
