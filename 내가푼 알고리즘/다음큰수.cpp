#include <string>
#include <vector>
using namespace std;

 int  CountOne(int n){
     int cnt=0;
    for(int i=0;i<31;i++){
        if(n&0x01<<i){
            cnt++;
        }
    }
    printf("cnt:%d\n",cnt);
    return cnt;  
}

int solution(int n) {
    int answer = 0;
    int n_num=CountOne(n);
    int cmp_num=0;
    while(n_num!=cmp_num){
        n++;  
        cmp_num=CountOne(n);
    }
    answer=n;
    return answer;
}
