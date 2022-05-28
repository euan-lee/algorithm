#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    map<string,int> m;
    int s=0,e = 0;
    
    for(auto gem:gems){
        m[gem]=0;
    }
    
    int total_gems = m.size();
    int cur_gems = 0;
    int tmp_s,tmp_e;
    int len = 987654321;
    while(true){
        if(cur_gems==total_gems){
            if(e-s < len){
                tmp_s = s;
                tmp_e = e;
                len = e-s;
            }
            
            if(m[gems[s]]>1){
                m[gems[s]]--;
                s++;
            } else{
                m[gems[s]]--;
                s++;
                cur_gems--;
            }
            
        }else{
            if(e==gems.size()) break;
            if(!m[gems[e]]) cur_gems++;
            m[gems[e]]++;
            e++;
        }
    }
    answer.push_back(tmp_s+1);
    answer.push_back(tmp_e);
    
    return answer;
}
