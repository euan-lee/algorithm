#include <string>

#include <vector>

#include <algorithm>

using namespace std;

vector<string> arr;

string temp[5] = {"A", "E", "I", "O", "U"};

void go(int maxlen, string s) {

    if(maxlen == s.size()) {

        arr.push_back(s);

        return;

    }

    

    for(int i=0 ; i<5 ; i++) {

        go(maxlen, s+temp[i]);

    }

}

int solution(string word) {

    int answer = 0;

    for(int i=1 ; i<=5 ; i++) {

        go(i, "");

    }

    

    sort(arr.begin(), arr.end());

    answer = find(arr.begin(), arr.end(), word)-arr.begin()+1;

    

    return answer;

}
