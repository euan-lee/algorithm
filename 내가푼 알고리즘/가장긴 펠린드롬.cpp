#include <iostream>
#include <string>
using namespace std;

int solution(string s)
{
   // s = "abcdee";
    if(s.size()==0)return 0;
    int answer=-1;
    int cnt;
    int start;
    int end;
    for(int i=0;i<s.size();i++){
        cnt=0;
        start=i;
        end=i;
        while(1){
            if(start<0||end>=s.size())break;
            if(s[start]!=s[end])break;
            if(s[start]==s[end]){
                cnt++;
            }
            start--;
            end++;
        }
        cnt=2*(cnt-1)+1;
        answer=max(answer,cnt);
        }
   for(int i=0;i<s.size();i++){
       start=i;
       end=i+1;
       cnt=0;
       while(1){
       if(start<0||end>=s.size())break;
       if(s[start]!=s[end])break;
       if(s[start]==s[end]){
          cnt++;
       }
       start--;
       end++;
    } 
    cnt=2*(cnt);
    answer=max(answer,cnt);
   } 
    return answer;
}
