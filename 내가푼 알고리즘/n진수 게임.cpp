#include <string>
#include <vector>

using namespace std;

string solution(int n, int t, int m, int p) {
   // t=1000;
    //n은 n진법
    //n진법->1의자리수 n개,2의자리수(n-1)*n*2개,3의자리수3*(n-1)*n*n개
    int temp=n-1;
    int num=temp;
    int k_num=0;
    for(int k=2;k<100;k++){//k자리수
        temp=temp*n;
        num=num+temp;
        if(num>t){
            num=num-temp;
            k_num=k;
            break;
        }
    }
    //num,k_num번쨰 수1000000(0개수 k만큼 있음)
    
    printf("%d번째 자리 수에서 %d만큼 떨어짐\n",k_num,t-num);
    //t는 숫자 갯수
    //게임 참가인원 m
    //튜브 순서 p
    string answer = "";

    return answer;//
}
