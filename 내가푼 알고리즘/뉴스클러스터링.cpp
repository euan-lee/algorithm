#include <string>
#include <unordered_map>
#include<algorithm>
#include <iostream>
using namespace std;

int solution(string str1, string str2) {
    int answer = 0;
    vector<string> B;
    vector<string> A;
    //1.첫번쨰 문자열 소문자로 변환
    for(int i=0;i<str1.size();i++){
         if(str1[i]>='A'&&str1[i]<='Z'){
            str1[i]=tolower(str1[i]);
         }
    }
    //2.두번쨰 문자열 소문자로 변환
       for(int i=0;i<str2.size();i++){
         if(str2[i]>='A'&&str2[i]<='Z'){
            str2[i]=tolower(str2[i]);
         }
    }
    //3.첫번쨰 문자열 돌려서 A총 개수 구하기
    for(int i=0;i<str1.size()-1;i++){
        if(str1[i]>='a'&&str1[i]<='z'&&str1[i+1]>='a'&&str1[i+1]<='z'){ 
            A.push_back(str1.substr(i,2));
        }
        else{
            continue;
        }
    }
     //4.B총 개수 구하기
    for(int i=0;i<str2.size()-1;i++){
        if(str2[i]>='a'&&str2[i]<='z'&&str2[i+1]>='a'&&str2[i+1]<='z'){ 
            B.push_back(str2.substr(i,2));
        }
        else{
            continue;
        }
    }
    //6.(AnB)를 어떻게 구하지? 
    vector<string> c;
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    
    set_intersection(A.begin(),A.end(),B.begin(),B.end(),back_inserter(c));
   
    
    vector<string> d;
    set_union(A.begin(),A.end(),B.begin(),B.end(),back_inserter(d));
    printf("a%d b:%d\n",A.size(),B.size());
    //8.자카드 유사도
    if(d.size()==0)return 65536;
    answer=65536*(c.size())/(d.size());
    return answer;
}
