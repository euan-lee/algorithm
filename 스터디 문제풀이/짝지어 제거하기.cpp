#include <iostream>
#include <string>
#include <stack>

using namespace std;

int solution(string s)
{
    int answer = 0;
    // 홀수는 무조건 하나가 남습니다.
    if(s.empty() || s.size() % 2 != 0)
        return answer;

    stack<char> stk;
    for(size_t nIndex = 0; nIndex < s.size() ; ++nIndex)
    {
        if(stk.empty() || stk.top() != s[nIndex])
            stk.push(s[nIndex]);
        else
            stk.pop();
        
    }

    if(stk.empty())
        ++answer;

    return answer;
}
