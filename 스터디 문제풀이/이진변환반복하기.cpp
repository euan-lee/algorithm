[프로그래머스/Level 2] 이진 변환 반복하기 (C++)검색하기 블로그 홈

알고리즘 문제풀이/프로그래머스

[프로그래머스/Level 2] 이진 변환 반복하기 (C++)

숭황

2021. 1. 13. 15:56

 

programmers.co.kr/learn/courses/30/lessons/70129

 

코딩테스트 연습 - 이진 변환 반복하기

 

programmers.co.kr

1. 무한루프 안에서 문자열 s의 모든 0을 제거합니다.

2. 제거할 때마다 제거한 횟수를 더해줍니다.

3. 0이 제거된 문자열의 길이를 2진수로 변환해줍니다.

4. 변환이 끝나고 변환한 횟수를 더해줍니다.

5. 이러한 과정을 문자열의 길이가 1이 될 때까지 반복합니다. 

 

#include <string>

#include <vector>

using namespace std;

string getBinary(int num) {

    string strBinary = "";

    while(1) {

        if(num == 0) break;

        strBinary.insert(0, to_string(num % 2));

        num /= 2;

    }

    return strBinary;

}

vector<int> solution(string s) {

    vector<int> answer;

    int transCnt = 0, delCnt = 0;

    while(1) {

        if(s.size() == 1) {

            answer.push_back(transCnt);

            answer.push_back(delCnt);

            break;

        }

        for(int i = 0; i < s.size(); i++) {

            if(s[i] == '0') {

                s.erase(i--, 1); // s 문자열의 0이 삭제되면서 길이가 줄어드므로, 인덱스 위치 갱신이 필요 

                delCnt++;

            }

        }

        s = getBinary(s.size());

        transCnt++;

    }

    return answer;

}
