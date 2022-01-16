#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int n,m;
int arr[1000];
int copy_arr[1000];
bool visited[1000];
int result=0;
int max1=0;

void combi(int x){
    if(x==3){
    result=copy_arr[0]+copy_arr[1]+copy_arr[2];
    if(max1<result&&max1<m){
        max1=result;
    }
    return;
    }  
    
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i]=1;
            copy_arr[x]=arr[i];
            combi(x+1);
            visited[i]=0;
        }
    }
}



int main(){
    int max=0;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
    }
    for(int i=0;i<n;i++){
        visited[i]=1;
        copy_arr[0]=arr[i];
        combi(1);
    }
    printf("%d\n",max1);
}