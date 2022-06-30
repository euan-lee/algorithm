#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int row[20];
int visited[20];

bool Check(int n,int r,int cnt,vector<vector<string>> &relation){
    if(cnt==r){   
        unordered_map<string,int> mile_stone;
        printf("hash에 넣음\n");
        for(int i=0;i<r;i++){
            for(int k=0;k<relation.size();k++){
                printf("%s\n",relation[k][row[i]].c_str());
                mile_stone[k]=1;    
            }
        }
        for(int i=0;i<mile_stone.size();i++){
        
            return true;
        }
        printf("-----");
        return false;
    }
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i]=1;
            row[cnt]=i;
            Check(n,r,cnt+1,relation);
            visited[i]=0;    
        }
    }
    return false;
}


int CombinationAll(int n,vector<vector<string>> &relation){
    bool flag=false;
    for(int i=0;i<n;i++){
        flag=Check(n,i+1,0,relation);
        if(flag==true){
            return i+1;   
        }
    }
    return 100000;
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    int tuple_size=relation.size();
    int candidate_key=relation[0].size();
     row[20]={0,};
     visited[20]={0,};
    answer=CombinationAll(candidate_key,relation);
    return answer;
}
