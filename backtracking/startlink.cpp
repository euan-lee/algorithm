#include <iostream>
#include <vector>
#include <algorithm>
#define max_int 21
/*
 최소값 구할때 제일 큰값으로 초기화하는데
 얼마인지 계산하기 귀찮을때, 단, 변수의 최대 크기가 int범위 안에 들어올때
 2147483647 로 초기화 합니다.
 
 리듬감 있게 외우면 20초 이내에 외워집니다.
 이일~ 사칠사팔~ 삼육사칠~
 */
#define max_val 2147483647
using namespace std;

/*
 시간 복잡도: O(nCn/2 + n^2)
 공간 복잡도: O(n^2)
 사용한 알고리즘: 순열(next_permutation)
 사용한 자료구조: 배열, 리스트
 */

int n, a[max_int][max_int], start_sum, link_sum, start_first, start_second, link_first, link_second, result = max_val;

// 스타트, 링크 팀에 속한 사람들의 번호를 저장할 리스트를 벡터로 생성
vector<int> start, link;

// 최소값 반환
int min(int a, int b){
    return a < b ? a : b;
}

// 절대값 반환
int abs(int a){
    if(a < 0) a = a * -1;
    return a;
}

int main(){
    // 1. 입력
    scanf("%d", &n);
    
    // 2차원 배열에 힘의 정보를 입력받습니다.
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    
    // 2. 순열 수행
    // 순열을 저장할 리스트 v를 벡터로 생성합니다.
    vector<int> v;
    for(int i=0; i<n/2; i++) v.push_back(0);
    for(int i=0; i<n/2; i++) v.push_back(1);
    do{
        //스타트팀, 링크팀을 만들고
        vector<int> start, link;
        for(int i=0; i<(int)v.size(); i++){
            // 0일때 스타트팀에 넣어줍니다.
            if(v[i] == 0) start.push_back(i + 1);
            // 1일때 링크팀에 넣어줍니다.
            else link.push_back(i + 1);
        }
        
        start_sum = 0;
        link_sum = 0;
        
        // 2중 for문으로 돌면서 각 팀의 선수를 고릅니다. O(n^2)
        for(int i=0; i<n/2; i++){
            for(int j=i+1; j<n/2; j++){
                if(i == j)continue;
                
                // 1) 스타트팀 2명 골라서
                start_first = start[i];
                start_second = start[j];
                
                // 스타트팀 점수 계산
                start_sum += a[start_first][start_second] + a[start_second][start_first];
                
                // 2) 링크팀 2명 골라서
                link_first = link[i];
                link_second = link[j];
                
                // 링크팀 점수 계산
                link_sum += a[link_first][link_second] + a[link_second][link_first];
            }
        }
        
        // 절대값을 취해주고, 최소값을 갱신해줍니다.
        result = min(result, abs(start_sum - link_sum));
        
    }while(next_permutation(v.begin(), v.end()));
    
    // 3. 출력
    printf("%d\n", result);
}
