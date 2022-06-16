#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;

int solution(vector<int> A, vector<int> B)
{
    int answer = 0;
    int sum=0;
    sort(A.begin(),A.end());
    sort(B.begin(),B.end(),greater<int>());
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    for(int i=0;i<A.size();i++){
        sum=sum+A[i]*B[i];
    }
    cout << "Hello Cpp" << endl;
    answer=sum;
    return answer;
}
