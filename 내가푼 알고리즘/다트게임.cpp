#include <string>
#include<cmath>
#include<vector>
using namespace std;

int solution(string dartResult) {
    int answer = 0;
    vector<int> v;
    for(int i=0;i<dartResult.size();i++){
        if(dartResult[i]=='S'||dartResult[i]=='D'||dartResult[i]=='T'){
            int exponent=1;
            if(dartResult[i]=='S'){
                exponent=1;
            }
            else if(dartResult[i]=='D'){
                exponent=2;
            }else{
                exponent=3;
            }
            int bonus=1;
            if(dartResult[i+1]=='#'||dartResult[i+1]=='*'){
                if(dartResult[i+1]=='#'){
                    bonus=-1;
                }else if(dartResult[i+1]=='*'){
                    bonus=2;
                } 
            }
            int number=0;
            if(dartResult[i-2]=='1'){//앞 숫자가 10이라면
               number=10;
            }else{
                number=dartResult[i-1]-'0';
                
            }
            int temp_s=0;
            if(bonus==-1){
                temp_s=pow(number,exponent)*bonus;
                v.push_back(temp_s);
            }else if(bonus==2){
                if(v.size()!=0){
                    int temp=v.back();
                    v.pop_back();
                    temp=temp*bonus;
                    printf("prev:%d\n",temp);
                    v.push_back(temp);    
                }
                temp_s=pow(number,exponent)*bonus;
                v.push_back(temp_s);
            }else{
                temp_s=pow(number,exponent)*bonus;
                v.push_back(temp_s);
            }
        }
    }
    for(int i=0;i<v.size();i++)answer=answer+v[i];
        return answer;
    }
