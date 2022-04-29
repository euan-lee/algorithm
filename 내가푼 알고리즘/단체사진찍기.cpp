#include <string>
#include <vector>
#include<iostream>
using namespace std;

char Check[9]={'X','X','X','X','X','X','X','X'};
char Friends[9]={'A','C','F','J','M','N','R','T'}; 
int visited[8]={0,};
int seat=0;
int result=0;
int answer=0;
int count=0;
void Permutation(int seat,vector<string> data){
    
    int first=-100;
    int second=-100;
    if(seat==8){//문자열 8! 나열
    for(int i=0;i<data.size();i++){//조건 들어오는 거
        for(int j=0;j<8;j++){//문자열 검사
            
            if(Check[j]==data[i][0]){
                first=j;
            }
            
            if(Check[j]==data[i][2]){
                second=j;
            }
        }//검사 끝 거리 확인
        
        int Dist = data[i][4] - '0';//부호 확인
        
        int range=abs(first-second);//두개의 절대거리
         
         if(data[i][3]=='='){
             if(range!=Dist){
             answer--; 
             }
         }

    }
            
    answer++;
    return ;
    }
    
    for(int i=0;i<8;i++){    
        if(visited[i]==0){       
        visited[i]=1;
        Check[seat]=Friends[i];
        seat++;
        Permutation(seat,data);
        visited[i]=0;
        seat--;
    }
    }

};



int solution(int n,vector<string> data){
    Permutation(seat,data);
    printf("answer:%d\n",answer);
    return answer;
}
