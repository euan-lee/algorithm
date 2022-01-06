#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
 
vector<int> solution(string s) {
    vector<int> answer;
 
    vector<int> tmp;
    vector < pair<int, vector<int> > > vt;
 
    int size = s.size();
    int num = 0;
 
//양끝 괄호는 무시하고 시작
    for (int i = 1; i < size - 1; i++) {
        if (s[i] == '{') continue;
 
        if (s[i] == '}') {
            tmp.push_back(num);
 
            //원소를 넣어줬던 tmp벡터를 vt벡터에 tmp벡터의 크기와 pair로 같이 넣어준다.
            vt.push_back(make_pair(tmp.size(), tmp));
            
            //num은 0으로 초기화하고 다음 원소를 넣어주기 위해 tmp벡터도 초기화
            num = 0;
            tmp.clear();
        }
        else if (s[i] == ',') {
            if (s[i - 1] == '}') continue; //이전 원소와 구분하는 쉼표라면 넘어간다.
            
            //숫자가 만들어졌으므로 벡터에 넣어주고 num은 0으로 초기화
            tmp.push_back(num);
            num = 0;
        }
        else {
            //원소(숫자)인 경우
            num *= 10;
            num += (s[i] - '0');
        }
    }
 
    sort(vt.begin(), vt.end());
 
    set<int> res;
    for (pair<int, vector<int>> p : vt) {
        //p.first: 벡터 크기, p.second: 원소 값
        for (int num : p.second) {
            //원소가 중복되지 않는다면 set에 추가해주고, answer 벡터에도 추가해준다.
            if (res.find(num) == res.end()) {
                res.insert(num);
                answer.push_back(num);
            }
        }
    }
 
 
    return answer;
}
