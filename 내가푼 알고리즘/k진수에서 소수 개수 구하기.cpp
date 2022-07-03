#include <string>
#include <vector>

using namespace std;

int solution(int n, int k) {
    int answer = -1;
    //n을 k진법으로 변환(문자열)
    string temp="";
    while(n!=0){
        temp=to_string(n%k)+temp;
        n=n/k;
    } 
    printf("%s\n",temp.c_str());
    //0을 기점으로 투포인터를 사용,문자열 잘라서 구분
    int start=0;
    int end=0;
    string param="";
    for(int i=0;i<temp.size();i++){
        if(temp[i]=='0'){
            param=temp.substr(start,end-start-1);
            start=end;
            printf("%s\n",param.c_str());
        }else{
            end++;
        }
    }
    return answer;
}
