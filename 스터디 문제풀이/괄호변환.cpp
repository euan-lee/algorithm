
#include <string>
 
using namespace std;
bool check(string p) {
    int t{};
    for (size_t i = 0; i < p.length(); i++) {
        if (p[i] == '(')       t++;
        else {
            if (!t)     return false;
            t--;
        }
    }
    return true;
}
 
string recursion(string p) {    if (p == "")    return p;
    string u{}, v{};
    int Lcount{}, Rcount{};
    for (size_t i = 0; i < p.length(); i++) {
        if (p[i] == '(')     Lcount++;
        else        Rcount++;
        if (Lcount == Rcount) {
            u = p.substr(0, i + 1);
            v = p.substr(i + 1);
            break;
        }
    }
    if (check(u))     return u + recursion(v);
    else{
        string temp{ "(" };
        temp += recursion(v) + ")";
        u = u.substr(1, u.length()-2);
        for (size_t i = 0; i < u.length(); i++) {
            if (u[i] == '(')    temp += ')';
            else    temp += '(';
        }
        return temp;
    }
}
 
string solution(string p) {
    if (check(p))     return p;
    return recursion(p);
}
