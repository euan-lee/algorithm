2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
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
