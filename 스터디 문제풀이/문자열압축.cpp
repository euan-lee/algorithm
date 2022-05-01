#include <string>
#include <vector>
 
using namespace std;
 
int Min(int A, int B) { return A < B ? A : B; }
 
int solution(string s) 
{
    int answer = s.length();
    for (int Len = 1; Len <= s.length() / 2; Len++)
    {
        /* 압축할 단위는 1개부터 , 문자열의 길이까지 압축이 가능하므로 모든 경우 탐색. */
        /* Result = 압축해서 나온 새로운 문자열을 저장할 변수 */
        /* Temp = 현재 압축해서 비교를 하기 위한 문자열 */
        /* Cnt = Temp가 현재까지 나온 횟수. */
        string Result = "";
        string Temp = s.substr(0, Len);
        int Cnt = 1;
        int i;
        for (i = Len; i <= s.length(); i = i + Len)
        {
            /* Temp와 그 다음 자른 문자열이 동일하면, Cnt++ */
            /* 그게 아니라면 , Result에 Temp를 옮기고, Temp에 새로운 문자열을 저장.*/
            if (Temp == s.substr(i, Len)) Cnt++;
            else
            {
                if (Cnt == 1) Result += Temp;
                else
                {
                    Result += to_string(Cnt);
                    Result += Temp;
                }
                
                Temp = s.substr(i, Len);
                Cnt = 1;
            }            
        }
 
        /* 예외적인 경우. 문자열의 길이를 넘어서서, 마지막 몇 개의 문자가 짤리는 경우가 발생. */
        /* 이 경우에는, 문자열이 짤리지 않도록 하기 위해서, 한번 더 진행. */
        if (i > s.length())
        {
            if (Cnt == 1) Result += Temp;
            else
            {
                Result += to_string(Cnt);
                Result += Temp;
            }
        }
        answer = Min(answer, Result.length());
    }
    return answer;
}

