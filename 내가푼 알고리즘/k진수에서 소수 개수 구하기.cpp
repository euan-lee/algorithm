#include <string>
#include <vector>
using namespace std;

bool IsPrime(long long n){
    if(n==1||n==0){
        return false;
    }
    if(n==2)
        return true;
    
    for(long long i=2;i<n;i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

int solution(int n, int k){
    int answer=0;
    vector<int> v;
    //n을 k진법으로 변환(문자열)
    string temp="";
    while(n!=0){
        temp=to_string(n%k)+temp;
        n=n/k;
    }
    
    printf("%s\n",temp.c_str());
    v.push_back(0);
    for(int i=0;i<temp.size();i++){
        if((temp[i]=='0'&&temp[i+1]!='0')||temp[i]=='0'&&temp[i-1]!='0'){
            v.push_back(i);
        } 
        if(i==temp.size()-1){
            if(temp[i]!='0'){
                v.push_back(i+1);
            }
        }
    }
    if(v.size()==1)return 1;
   for(int i=0;i<v.size()-1;i++){
       string val_String=temp.substr(v[i],v[i+1]-v[i]);
       printf("%s\n",val_String.c_str());
       if(IsPrime(stol(val_String))){
           answer++;
       }
   }
    return answer;
}
