#include <string>
#include <vector>
 #include<algorithm>
using namespace std;

long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end());
    long long answer = 0;
    long long s=1;
    long long e=(long long)times[times.size()-1]*n;
    long long m;
    while(s<=e){
        
        m=(s+e)/2;
        long long cnt=0;
        for(int i=0;i<times.size();i++){
            cnt=cnt+m/times[i];
        }
      
        if(cnt<n){
            s=m+1;
        }
        else{
            if(m<=e){
                answer=m;
            }
            e=m-1;
        }
    }
    return answer;
}
