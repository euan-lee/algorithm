#include<string>
#include <iostream>
#include <stack>
using namespace std;

bool solution(string s)
{
    bool answer = true;
    stack<char> st;
    //문자열 스택에 넣기 
    for(int i=0;i<s.size();i++){
        //case1:(->stack에 넣기
        if(s[i]=='('){
            st.push(s[i]);
        }
        //case2:)->stack이 비어있지 않다면 stack pop 
        else if(st.size()!=0&&s[i]==')'){
            st.pop();    
        }
        else{
            return 0;
        }   
    }
    //for문 종료후 stack이 empty라면 return 1 아니라면 return 0;
    if(st.size()!=0){
        return 0;
    }
    else{
        return 1;
    } 
    
  
 
}
