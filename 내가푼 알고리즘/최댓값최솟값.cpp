#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

string solution(string s) {
    string answer = "";
    istringstream ss(s);
    string stringBuffer;
    vector<int> x;
    x.clear();
    while (getline(ss,stringBuffer, ' ')){
        x.push_back(stoi(stringBuffer));
    }
    sort(x.begin(),x.end());
    answer=to_string(x.front())+" "+to_string(x.back());
    
    printf("%s",answer.c_str());
    return answer;
}
