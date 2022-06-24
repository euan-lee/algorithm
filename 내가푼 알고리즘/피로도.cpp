#include <string>
#include <vector>
using namespace std;

int visited[8];
int perm[8];
int max_cnt;
void dfs(int n,int k,vector<vector<int>>& dungeons){
    if(n==dungeons.size()){
        int sum=0;
        int k_temp=k;
        
        int cnt=0;
        for(int i=0;i<8;i++){
            if(visited[i]!=-1){
                    if(k_temp>=dungeons[perm[i]][0]){
                        k_temp=k_temp-dungeons[perm[i]][1];
                        cnt++;
                    }
                }
        }
         max_cnt=max(cnt,max_cnt);
        return ;
    }
    for(int i=0;i<dungeons.size();i++){
        if(visited[i]==-1){
            visited[i]=1;
            perm[n]=i;
            dfs(n+1,k,dungeons); 
            visited[i]=-1;
        }
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    max_cnt=0;
    visited[8]={0,};
    perm[8]={0,};
    for(int i=0;i<8;i++){
        visited[i]=-1;
        perm[i]=0;
    }
    dfs(0,k,dungeons);
    answer=max_cnt;
    return answer;
}
