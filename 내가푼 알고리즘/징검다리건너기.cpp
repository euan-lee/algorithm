#include <string>
#include <vector>
#include<algorithm>
using namespace std;

bool TwoPointer(vector<int> &stones,int mid,int k){
    int start=0;
    int end=0;
    for(int i=0;i<stones.size();i++){
        if(stones[i]-mid<0){
            end++;
        }else{
            start=i;
            end=start;
        }    
      //  printf("s:%d e:%d\n",start,end);
        if(end-start>=k)return false;
    }
    return true;
}

int solution(vector<int> stones,int k) {
    int answer=0;
    int start=0;
    int end=200000000;
    int mid=0;
    while(start<=end){
        mid=(start+end)/2;
      //  printf("start:%d mid:%d end:%d",start,mid,end);
        bool flag=TwoPointer(stones,mid,k);
        printf(" flag:%d\n",flag);
        if(flag==true){
            answer=mid;
            start=mid+1;
        }else{
            end=mid-1;
        }
      //  printf("%d ",mid);
    }
    return answer;
}
