#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int N;
int number[]={0,};
int operation[4]={0,};
int maximum=-100000;

void cal(int n){
    if(n==N){
        for(int i=0;i<n;i++){
          //  printf("the answer is %d",number[i]);
        }
         return;
    }
    for(int i=0;i<4;i++){
          if(operation[i]>0){
            operation[i]--;
            if(i==0){
                number[n]=number[n]+number[n-1];
                printf("number+%d",number[n]);
                cal(n+1);
            }
            else if(i==1){
                number[n]=number[n]-number[n-1];
                printf("number-%d",number[n]);
                cal(n+1);
            }
            else if(i==2){
                number[n]=number[n]*number[n-1];
                cal(n+1);
            }
            else if(i==3){
                number[n]=number[n]/number[n-1];
                printf("number/%d",number[n]);
                cal(n+1);
            }
          }
    }
}


 int main(){
      cin >> N;
    for(int i=0;i<N; i++){
           cin >> number[i];
    }
     


    for(int i=0;i<4;i++)
       cin >> operation[i];

    for(int i=0;i<2; i++)
        printf("i:%d number is: %d\n",i,number[i]);
           
    cal(0);

 }



