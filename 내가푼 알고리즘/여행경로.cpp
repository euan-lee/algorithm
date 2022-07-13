#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int last;
void Dfs(int way_num,vector<int> &visited,vector<vector<string>> &tickets,vector<string>&answer){
    last=way_num;
    visited[way_num]=1;
    answer.push_back(tickets[way_num][0]);
    for(int i=0;i<tickets.size();i++){
        if(visited[i]!=1){
            if(tickets[way_num][1]==tickets[i][0]){
                Dfs(i,visited,tickets,answer);  
            }  
        }
    }
}
vector<string> solution(vector<vector<string>> tickets) {
    tickets={{"ICN","B"}, {"B","C"},{"C","ICN"},{"ICN","D"},{"ICN","E"}, {"E","F"}};
    last=0;
    vector<string> answer;
    vector<int> visited;
    string start=tickets[0][0];
    int index=0;
    sort(tickets.begin(),tickets.end());
    for(int i=0;i<tickets.size();i++){
        visited.push_back(0);
    }
    
    for(int i=0;i<tickets.size();i++){
        if(start==tickets[i][0]){
            index=i;
            break;
        }
    }
    Dfs(index,visited,tickets,answer);
    answer.push_back(tickets[last][1]);
    return answer;
}
