#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
vector<string> combination;
int column = 0;
 
bool compare(string& a, string& b) {
    if (a.length() != b.length())     return a.length() < b.length();
    return a < b;
}
void Combination(int k = 0, string temp = "") {
    for (int i = k; i < column; i++) {
        temp += to_string(i);
        combination.push_back(temp);
        Combination(i + 1, temp);
        temp = temp.substr(0, temp.length() - 1);
    }
}
 
bool subset(vector<vector<string>>& relation, string com) {
    map<string, int> candidateCheck;
    for (int i = 0; i < relation.size(); i++) {
        string temp = "";
        for (int k = 0; k < com.length(); k++) {
            int number = com[k] - '0';
            temp += relation[i][number] + " ";
        }
        temp = temp.substr(0, temp.length() - 1);
        if (candidateCheck[temp])    return false;
        candidateCheck[temp]++;
    }
    return true;
}
 
int solution(vector<vector<string>> relation) {
    int answer = 0;
    column = relation[0].size();
    Combination();
    sort(combination.begin(), combination.end(), compare);
    for (int i = 0; i < combination.size(); i++) {
        if (subset(relation, combination[i])) {
            string temp = combination[i];
            for (int j = combination.size() - 1; j >= i; j--) {
                bool check = true;
                for (auto t : temp) {
                    if (combination[j].find(t) == string::npos) {
                        check = false;
                        break;
                    }
                }
                if (check)    combination.erase(combination.begin() + j);
            }
            i--;    answer++;
        }
    }
    return answer;
}
