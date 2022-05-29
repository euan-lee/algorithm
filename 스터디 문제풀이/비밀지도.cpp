#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

vector<string> change_block(vector<int>& arr) {
    vector<string> s;
    for (int i = 0 ; i < arr.size(); i++) {
        string tmp;
        int two_pow = pow(2,arr.size() - 1);
        int r = arr[i];
        for ( int j = 0 ; j < arr.size() ; j++) {
            if (r / two_pow == 1) {
                r %= two_pow;
                tmp += "#";
            } else {
                tmp += " ";
            }
            two_pow /= 2;
        }
        s.push_back(move(tmp));
    }
    return s;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> arr_1 = move(change_block(arr1));
    vector<string> arr_2 = move(change_block(arr2));
    vector<string> answer;
    for (int i = 0 ; i < arr1.size(); i++) {
        string s;
        for(int j = 0; j < arr1.size(); j++) {
            //cout << arr_1[i][j];
            if (arr_1[i][j] ==  ' ' && arr_1[i][j] == arr_2[i][j]) {
                s += " ";
            } else{
                s += "#";
            }
        }
        answer.push_back(move(s));
    }
    
    return answer;
}
