#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> solution(vector<string> record) {
    int start=0;
    int end=0;
    for(int i=0;i<record.size();i++){
        for(int j=0;j<record[i].size();j++){
            if(record[i][j]==' '){
             end=j;
             printf("start:%d end:%d\n",start,end);
             printf("sperated:%s\n",record[i].substr(start,end-start).c_str());   
            start=j;
            }
        }
        printf("");
       printf("sperated:%s\n",record[i].substr(start,record[i].size()).c_str());  
        start=0;
        //문자열 분리
        
        //enter 아이디 닉네임으로 분리(시간복잡도 계산은 어떻게??)
        
        //
        
    }
    
    vector<string> answer;
    return answer;
}
