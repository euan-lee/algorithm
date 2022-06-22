#include <string>
#include <vector>
using namespace std;
vector<int>graph[101];
int visited[10];
int answer;

void  Dfs(int root){
    if(root==0){
        printf("end\n");
        return ;
    }
    printf("node:%d",root);
    visited[root]=1;
    answer++;
    for(int i=0;i<graph[root].size();i++){
        if(graph[root][i]!=0&&visited[graph[root][i]]==0){
            Dfs(graph[root][i]);
        }
    }
    visited[root]=0;
    return;
}

int solution(int n, vector<vector<int>> wires) {
    int total_size=0;
    int temp_root=0;
    int minimun=10;
    visited[10]={0,};
    answer=0;
    for(int i=0;i<wires.size();i++){
        graph[wires[i][0]].push_back(wires[i][1]);
        graph[wires[i][1]].push_back(wires[i][0]);
    }  
    
    for(int i=1;i<=n;i++){
        for(int j=0;j<graph[i].size();j++){ 
            for(int k=0;k<graph[graph[i][j]].size();k++){
                if(graph[graph[i][j]][k]==i){
                    int weight_temp_1=graph[i][j];
                    int weight_temp_2=graph[graph[i][j]][k];
                    printf("%d %d\n",graph[graph[i][j]][k],graph[i][j]);
                    graph[graph[i][j]][k]=0;
                    graph[i][j]=0;
                    printf("----\n");
                    Dfs(i);
                     printf("----\n");
                    minimun=min(abs(n-2*answer),minimun);
                    answer=0;
                    graph[i][j]=weight_temp_1;
                    graph[graph[i][j]][k]=weight_temp_2;
                }    
            }
            printf("\n");
        }
        
    }  
    answer=minimun;
    return answer;
}
