#include <string>
#include <vector>
using namespace std;
vector<char> record_operator;
vector<long long> record_operand;
string temp = "";
char perm[3]= {'+','-','*' };//+,-,*
int visited[3]={0,0,0};
char result[3] = { 'x','x','x' };


void Permutation(int seat){

    if(seat==3){
       for(int k=0;k<3;k++){
           printf("%c\n",result[k]);
           for(int y=0;y<record_operator.size();y++){//연산자 문자열 탐색 
               if(result[k]==record_operator[y]){
                  printf("find:%c\n",record_operator[y]);   
                  printf("index is:%d\n",y);
               }
           }
       }
        return;
    }
    
   for(int j=0;j<3;j++){
       if(visited[j]==0){
        result[seat]=perm[j];
       visited[j]=1;
       seat++;
       Permutation(seat);
       visited[j]=0;
       seat--;
       }
}
 
}


void seperate(string expression){
    for(int i=0;i<expression.length();i++){
        if(expression[i]=='0'||expression[i]=='1'||expression[i]=='2'||expression[i]=='3'||expression[i]=='4'||expression[i]=='5'||expression[i]=='6'||expression[i]=='7'||expression[i]=='8'||expression[i]=='9'){
            temp += expression[i];
        }
        
        else{//안 부호라면 operand에 푸시
            record_operator.push_back(expression[i]);
            record_operand.push_back(stoll(temp));   
            temp="";
        }     
    }
}

long long solution(string expression) {
    long long answer = 0;
    seperate(expression);//연산자와 부호 구분
    Permutation(0);
    
    return answer;
}
