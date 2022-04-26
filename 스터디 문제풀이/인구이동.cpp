1
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
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
 
#define endl "\n"
#define MAX 50
using namespace std;
 
int N, L, R;
int MAP[MAX][MAX];
int Visit[MAX][MAX];
int Country_Number;
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
bool Check = true;
 
void Input()
{
    cin >> N >> L >> R;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAP[i][j];
        }
    }
}
 
bool Can_Combination2(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < N && ny < N)
        {
            if (L <= abs(MAP[x][y] - MAP[nx][ny]) && abs(MAP[x][y] - MAP[nx][ny]) <= R) return true;
        }
    }
    return false;
} 
 
bool Can_Combination(int x, int y, int xx, int yy)
{
    if (L <= abs(MAP[x][y] - MAP[xx][yy]) && abs(MAP[x][y] - MAP[xx][yy]) <= R) return true;
    return false;
}
 
void BFS(int a, int b)
{
    queue<pair<int, int>> Q, Nq;
    Q.push(make_pair(a, b));
    Nq.push(make_pair(a, b));
    Visit[a][b] = true;
    int Sum = 0;
    int Cnt = 0;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
 
        Sum = Sum + MAP[x][y];
        Cnt = Cnt + 1;                                           
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
 
            if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
            if (Visit[nx][ny] != 0) continue;
            if (Can_Combination(x, y, nx, ny) == true)
            {
                Visit[nx][ny] = 1;
                Q.push(make_pair(nx, ny));
                Nq.push(make_pair(nx, ny));
            }
        }
    }
 
    int Value = Sum / Cnt;
    
    while (Nq.empty() == 0)
    {
        int x = Nq.front().first;
        int y = Nq.front().second;
        Nq.pop();
        MAP[x][y] = Value;
    }
}
 
void Print()
{
    cout << "########################################" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (Visit[i][j] == 0)
            {
                cout << 0 << " ";
            }
            else
            {
                cout << Visit[i][j] << " ";
            }
        }
 
        cout << "\t\t";
        for (int j = 0; j < N; j++)
        {
            cout << MAP[i][j] << " ";
        }
        cout << endl;
    }
    cout << "########################################" << endl;
 
}
 
void Solution()
{
    int Day = 0;
    while (Check)
    {
        //Print();
        Check = false;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {                    
                if (Visit[i][j] == 0 && Can_Combination2(i,j) == true)
                {
                    BFS(i, j);
                    Check = true;
                }
            }
        }        
        if (Check == true) Day++;
        memset(Visit, false, sizeof(Visit));
 
    }
    cout << Day << endl;
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
//    freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}
 
 
