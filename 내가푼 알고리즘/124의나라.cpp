#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(int n)
{
    string answer = "";
    vector<string> num = { "1", "2", "4" };

    while (true)
    {
        n = n - 1;
        
        answer = num[n % 3] + answer;
        
        if (n <= 0) break;
        n /= 3;
    }

    return answer;
}
