#include <iostream>
#include <string>
 
using namespace std;
 
string solution(string number, int k) {
    string answer = "";
    for (int j = 0, index = -1; j < number.length() - k; j++) {
        char max = 0;
        for (int i = index + 1; i <= k + j; i++) {
            if (max < number[i]) {
                index = i;
                max = number[i];
            }
        }
        answer += max;
    }
    return answer;
}
