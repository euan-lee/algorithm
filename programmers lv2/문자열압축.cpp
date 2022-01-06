#include <string>
#include <vector>
using namespace std;
 
int solution(string s) {
    int len = s.size();
    int answer = len;
 
    int n = len / 2;
 
 
    //i개 단위로 잘라서 압축
    for (int i = 1; i <= n; i++) {
 
        //i개 단위로 잘라서 압축한뒤 만들어지는 문자열
        string result = "";
 
        //자를 문자열 단위
        string ss = s.substr(0, i);
 
        int cnt = 1;
 
        //앞에서 자른 문자열 단위를 제외한 뒷부분(j번 문자부터) 문자열을 검사한다.
        for (int j = i; j <= len; j += i) {
            //j번 부터 i개 만큼이 문자열 단위와 똑같은 경우 cnt 증가
            if (ss == s.substr(j, i)) {
                cnt += 1;
            }
            else {
                //다른 경우 중 cnt가 1이면 result에 그대로 ss를 붙인다.
                if (cnt == 1) {
                    result += ss;
                }
                else {
                    //cnt가 1보다 크다면 cnt를 문자열 단위 앞에 붙여서 result에 이어준다.
                    result += (to_string(cnt) + ss);
                }
 
                //문자열 단위를 j번부터 i개로 변경 
                ss = s.substr(j, i);
                //cnt값 다시 1로 초기화
                cnt = 1;
            }
 
        }
 
        //문자열이 i로 나누어 떨어지지 않는다면 result에 나머지 부분을 붙여줘야한다.
        if ((len%i) != 0) {
            result += s.substr((len / i)*i);
        }
 
        //최솟값을 answer에 저장
        if (answer > result.size()) answer = result.size();
    }
 
 
    return answer;
}
