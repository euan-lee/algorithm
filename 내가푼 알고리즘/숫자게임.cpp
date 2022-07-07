#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    int a=0;
    int b=0;
    
    sort(A.begin(),A.end(),greater<int>());
    sort(B.begin(),B.end(),greater<int>());
    
    for(int i=0;i<A.size();i++)
    {
        if(A[a]<B[b])
        {
            b++;
            answer++;
        }
        a++;
    }
    return answer;
}
