#include <string>
#include <vector>
using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    int decimal=0;
    int cnt=0;
    int circle=0;
    while(1){
       
       if(s[0]=='1'&&s.size()==1)break;
        decimal=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='1'){
                decimal++;
            }
            else if(s[i]=='0'){
                 cnt++;
            }
        }
        s="";
        while(decimal/2!=0){
            decimal%2;
            s=std::to_string(decimal%2)+s;
            decimal=decimal/2;
        }
        s=to_string(decimal)+s; 
        circle++;
    }
    answer.push_back(circle);
    answer.push_back(cnt);
    return answer;
}
