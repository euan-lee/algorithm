#include <string>
#include <vector>
#include <cstring>

using namespace std;

int N;
vector<int> group;
vector<bool> rule_1;
vector<bool> rule_2;
vector<bool> used;
int w_idx;

struct info 
{
    int start, end, cnt;
};

bool check_rule_1(string& sentence, info l_info, char c)
{
    // 사용한적이 있는 소문자이면 X
    if (used[c - 'a'] == true)
    {
        return false;
    }
    // 소문자들의 맨 앞/뒤에서 한칸씩 더 나아간 자리가 sentence의 범위를 넘으면 X
    if (l_info.start - 1 < 0 || l_info.end + 1 >= N)
    {
        return false;
    }
    // 소문자들의 맨 앞/뒤에서 한칸씩 더 나아간 자리의 문자가 대문자가 아니면 X
    if (islower(sentence[l_info.start - 1]) || islower(sentence[l_info.end + 1]))
    {
        return false;
    }

    int l_cnt = 0, u_cnt = 0;
    for (int i = l_info.start - 1; i <= l_info.end + 1; ++i)
    {
        char now = sentence[i];
        if (islower(now))
        {
            // 현재 규칙체크중인 소문자이면: 그룹 인덱싱
            if (now == c)
            {
                group[i] = w_idx;
                ++l_cnt;
                u_cnt = 0;
            }
            // 1번규칙 체크중인데 중간에 다른문자가 있으면 X
            else
            {
                return false;
            }
        }
        else if (isupper(now))
        {
            l_cnt = 0;
            ++u_cnt;

            // 이미 같은 규칙이 적용되어 있으면 X
            if (rule_1[i] == true)
            {
                return false;
            }
            // 전에 규칙이 적용된적 없으면 그룹 인덱싱, 규칙적용 체크
            else 
            {
                group[i] = w_idx;
                rule_1[i] = true;
            }
        }
        
        // 같은 소문자 또는 (같거나 다른)대문자가 연속으로 있는 경우
        if (l_cnt > 1 || u_cnt > 1)
        {
            return false;
        }
    }

    // 단어 인덱스 증가 & 소문자 사용 체크
    ++w_idx;
    used[c - 'a'] = true;
    return true;
}

bool check_rule_2(string& sentence, info l_info, char c)
{
    // 사용한적이 있는 소문자이면 X
    if (used[c - 'a'] == true)
    {
        return false;
    }
    // 해당 소문자끼리의 거리가 2 미만이면 X
    if (l_info.end - l_info.start < 2)
    {
        return false;
    }

    // 2번 규칙의 앞뒤 소문자 그룹 인덱싱
    group[l_info.start] = w_idx;
    group[l_info.end] = w_idx;

    // 맨앞, 맨뒤 소문자 사이의 문자들을 검사
    for (int i = l_info.start + 1; i < l_info.end; ++i)
    {
        char now = sentence[i];
        
        if (isupper(now))
        {
            // 이미 같은 규칙이 적용되어 있으면 X
            if (rule_2[i] == true)
            {
                return false;
            }
            // 전에 규칙이 적용된적 없으면 그룹 인덱싱, 규칙적용 체크
            else 
            {
                group[i] = w_idx;
                rule_2[i] = true;
            }
        }
    }

    // 단어 인덱스 증가 & 소문자 사용 체크
    ++w_idx;
    used[c - 'a'] = true;
    return true;
}

// 같은 문자들의 맨 앞/뒤 인덱스와 개수 정보 구조체를 반환
info get_char_info(string& sentence, char c)
{
    int start = -1;
    int cnt = 0;
    int end = 0;
    for (int i = 0; i < N; ++i)
    {
        if (sentence[i] == c)
        {
            if (start < 0)
            {
                start = i;
            }
            ++cnt;
            end = i;
        }
    }
    return {start, end, cnt};
}

bool decrypting_possible(string &sentence)
{
    vector<bool> check_chars(26);
    for (int i = 0; i < N; ++i)
    {
        char now = sentence[i];

        // 암호화된 문자는 빈칸이 있으면 안됨
        if (now == ' ')
        {
            return false;
        }

        // 아직 체크되지 않은 문자라면
        if (group[i] == 0)
        {
            // 현재 문자가 대문자
            if (isupper(now))
            {
                // 마지막 문자일때: 현재 문자를 별개의 단어 취급
                if (i + 1 >= N)
                {
                    group[i] = w_idx++;
                    continue;
                }

                char next = sentence[i + 1];
                
                // 다음 문자가 대문자일때: 현재 문자를 별개의 단어 취급
                if (isupper(next))
                {
                    group[i] = w_idx++;
                }
                // 다음 문자가 소문자일때
                else if (islower(next))
                {
                    // 다음 문자(소문자)의 시작/끝 인덱스, 개수 정보 받아오기
                    info l_info = get_char_info(sentence, next);

                    // 다음 문자(소문자) 개수가 2개이면: 현재문자를 별개의 단어로 취급
                    if (l_info.cnt == 2)
                    {
                        group[i] = w_idx++;
                    }
                    /*
                        다음 문자(소문자) 개수가 2개가 아니면
                        : 다음 문자를 포함하는 단어가 규칙 1번 적용한지 확인
                    */
                    else
                    {
                        if (check_rule_1(sentence, l_info, next) == false)
                        {
                            return false;
                        }
                    }
                }
            }
            // 현재 문자가 소문자
            else if (islower(now))
            {
                // 현재 문자(소문자)의 시작/끝 인덱스, 개수 정보 받아오기
                info l_info = get_char_info(sentence, now);

                // 현재(소문자) 개수가 2개이면
                if (l_info.cnt == 2)
                {
                    /*
                        다음 문자가 대문자이고, 규칙 2번이 이미 적용된 상태라면
                        : 현재 문자를 포함하는 단어가 규칙 1번 적용한지 확인
                    */
                    if (isupper(sentence[i + 1]) && rule_2[i + 1])
                    {
                        if (check_rule_1(sentence, l_info, now) == false)
                        {
                            return false;
                        }
                    }
                    /*
                        그렇지 않으면
                        : 현재 문자를 포함하는 단어가 규칙 2번 적용한지 확인
                    */
                    else 
                    {
                        if (check_rule_2(sentence, l_info, now) == false)
                        {
                            return false;
                        }
                    }
                }
                // 현재(소문자) 개수가 2개가 아니면
                else
                {
                    // 현재 문자를 포함하는 단어가 규칙 1번 적용한지 확인
                    if (check_rule_1(sentence, l_info, now) == false)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

string make_answer(string &sentence)
{
    // last_idx : 첫번째 대문자 인덱스로 세팅
    int last_idx = 0;
    for (int i = 0; i < N; ++i)
    {
        if (isupper(sentence[i]))
        {
            last_idx = group[i];
            break;
        }
    }

    // 인덱스가 서로 다른 문자는 다른 단어로 취급하여 뒤에 ' ' 삽입
    string answer = "";
    for (int i = 0; i < N; ++i)
    {
        char c = sentence[i];
        if (isupper(c))
        {
            if (group[i] != last_idx)
            {
                answer += ' ';
            }

            answer += c;
            last_idx = group[i];
        }
    }
    return answer;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(string sentence) {

    N = sentence.size();
    group = vector<int>(N);
    rule_1 = vector<bool>(N);
    rule_2 = vector<bool>(N);
    used = vector<bool>(26);
    w_idx = 1;


    // 원복할 수 있는 문자열인지 검사
    bool result = decrypting_possible(sentence);

    // 원복할수 없는 문자열이면 invalid반환
    if (!result)
    {
        return "invalid";
    }

    return make_answer(sentence);
}
