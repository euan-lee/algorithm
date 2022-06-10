#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include <stack>




int IsRightString(string u){
    stack<char> s;
    for(int i=0;i<u.size();i++){
        if(u[i]=='('){
            s.push(u[i]);
        }
        else{
            if(s.size()==0) {
                return false;
            }
        s.pop();
        }       
    }
    if(s.size()==0){
        return 1;
    }
    else{
        return 0;
    }
}


string balanced(string bal){
    string u,v;
    int left=0;
    int right=0;
    if(bal.size()==0){
        return "";
    }  
    else{
        for(int i=0;i<bal.size();i++){     
            if(bal[i]=='('){
                left++;
            }
            else{
                right++;
            }
            if(left==right){
                u=bal.substr(0,i+1);
                v=bal.substr(i+1,bal.size());
                break;
            }
            else{
                u=bal;
                v="";        
            }  
        }
        printf("right:%d\n",right);
        printf("left:%d\n",left);
        printf("u:%s\n",u.c_str());
        printf("v:%s\n",v.c_str());
     //3-1 완료
        if(IsRightString(u)==1){
            return u+balanced(v);
        }
//4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다. 
//4-1,4-2
        else{//IsRightString(u)==0
            printf("4-2\n");
            v='('+balanced(v)+')';
            u.erase(0,1);
            u.erase(u.length()-1, 1);
            printf("4-2의 u:%s\n",u.c_str());
            printf("4-2의 v:%s\n",v.c_str());
            for(int i=0;i<u.size();i++){
                if(u[i]=='('){
                    u[i]=')';
                }
                else{
                    u[i]='(';
                }
            }
              printf("4-2의 변환u:%s\n",u.c_str());
           return v+u; 
        }
}
}

string solution(string p) {
    string answer = "";
    answer=balanced(p);
    return answer;
}
