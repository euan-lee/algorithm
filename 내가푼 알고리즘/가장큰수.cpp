#include<string>
#include<vector>
#include<algorithm> 
using namespace std;
bool Standard(string A, string B){    
    if (A + B > B + A) return true;    
    return false;
}
string solution(vector<int> numbers){   
    string Answer = "";    
    vector<string> Array;    
    for (int i = 0; i < numbers.size(); i++) Array.push_back(to_string(numbers[i]));    
    sort(Array.begin(), Array.end(), Standard);   
    for (int i = 0; i < Array.size(); i++)    Answer = Answer + Array[i];   
    if (Answer[0] == '0') Answer = "0";  
    return Answer;
}
