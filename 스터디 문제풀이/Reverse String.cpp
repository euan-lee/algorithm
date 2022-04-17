class Solution {
public:
    string reverseString(string s) {
        int i = 0; // from left to right
        int j = s.size() - 1;//from right to left
        while(i < j) { // stop until meet
            char tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            i++;
            j--;
        }
        return s;
    }
};
