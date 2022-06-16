#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
    double x=a;
    double y=b;
    int flag=1;
    int answer=0;
    while(flag==1){
        x=ceil(round(x/2));
        y=ceil((y/2));
        printf("x:%f y:%f\n",x,y);
        answer++;
      if(fabs(y-x)<0.00001){
          flag=0;
          printf("answer:%d\n",answer);
      }
  }
    return answer;
}
