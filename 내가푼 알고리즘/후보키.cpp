#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int row[20];
int visited[20];

bool Check(int n,int r,int cnt,vector<vector<string>> &relation){
    if(cnt==r){   
        unordered_map<string,int> mile_stone;
        for(int k=0;k<relation.size();k++){
            string temp="";
            for(int i=0;i<r;i++){
                temp=temp+relation[k][row[i]];
            }
            mile_stone.insert({temp,1}); 
            printf("%s:%d\n",temp.c_str(),mile_stone[temp]); 
        }
        printf("milesstone size is%d\n",mile_stone.size());
        printf("relation size is%d\n",relation.size());
        if(mile_stone.size()==relation.size()){
            return true;
        }
        else{
          return false; 
        }
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
        printf("check falg:%d %d\n",i,flag);
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
