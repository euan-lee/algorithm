#include <string>
#include <vector>
#include <algorithm>
#include<set>
using namespace std;

bool IsPrime(int num){
    if(num==1||num==0)return false;
    for(int i=2;i<num;i++){
        if(num%i==0){
            return false;
        }   
    }
    return true;

}

int solution(string numbers) {
    int answer = 0;
    set<int> s;
    sort(numbers.begin(), numbers.end());
    do {
      string temp;
        for(int i=0;i<numbers.size();i++){
            temp=temp+numbers[i];
            s.insert(stoi(temp));
        }
    } while (next_permutation(numbers.begin(),numbers.end()));
    
     
    for (auto it = s.begin(); it != s.end(); ++it){
        printf("%d\n",*it);
        if(IsPrime(*it)){
            answer++;
        }
    }



    return answer;
}
