#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int arr[10];
int check[10];
int use_arr[10];
int n;
int max_n = 0;

//식 계산하는 함수
int cal(){
    int result = 0;
    
    for(int i=0; i<n-1; i++){
        result += abs(use_arr[i] - use_arr[i+1]);
    }
    return result;
}

void dfs(int cnt){
    
    if(cnt == n){   //n개 다 각각의 순서에 배정
        max_n = max(max_n, cal());
        return;
    }
    
    for(int i=0; i<n; i++){
        if(check[i])    //이미 넣은지 확인
            continue;
        
        use_arr[cnt] = arr[i];
        check[i] = 1;   //넣은 거 표시
        dfs(cnt+1);
        check[i] = 0;   //재귀 끝나면 다시 뺀거로 표시
    }
}

int main (void){

    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    
    //첫번째 숫자 결정
    for(int i=0; i<n; i++){
        check[i] = 1;
        use_arr[0] = arr[i];
        dfs(1);
        check[i] = 0;
    }
    
    printf("%d\n", max_n);
}
