#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
int Check_State(int N, char C)
{
    if (N == 1)
    {
        if (C == 'c') return 1;
        if (C == 'j') return 2;
        if (C == 'p') return 3;
    }
    else if (N == 2)
    {
        if (C == 'b') return 1;
        if (C == 'f') return 2;
    }
    else if (N == 3)
    {
        if (C == 'j') return 1;
        if (C == 's') return 2;
    }
    else if (N == 4)
    {
        if (C == 'c') return 1;
        if (C == 'p') return 2;
    }
 
    return 0;
}
 
void Mapping_Group_Info(vector<int> Group_Info[4][3][3][3], string State, string Score)
{
    int L = Check_State(1, State[0]);
    int W = Check_State(2, State[1]);
    int C = Check_State(3, State[2]);
    int F = Check_State(4, State[3]);
    Group_Info[L][W][C][F].push_back(stoi(Score));
    Group_Info[0][W][C][F].push_back(stoi(Score));
    Group_Info[L][0][C][F].push_back(stoi(Score));
    Group_Info[L][W][0][F].push_back(stoi(Score));
    Group_Info[L][W][C][0].push_back(stoi(Score));
    Group_Info[0][0][C][F].push_back(stoi(Score));
    Group_Info[0][W][0][F].push_back(stoi(Score));
    Group_Info[0][W][C][0].push_back(stoi(Score));
    Group_Info[L][0][0][F].push_back(stoi(Score));
    Group_Info[L][0][C][0].push_back(stoi(Score));
    Group_Info[L][W][0][0].push_back(stoi(Score));
    Group_Info[0][0][0][F].push_back(stoi(Score));
    Group_Info[0][0][C][0].push_back(stoi(Score));
    Group_Info[0][W][0][0].push_back(stoi(Score));
    Group_Info[L][0][0][0].push_back(stoi(Score));
    Group_Info[0][0][0][0].push_back(stoi(Score));
}
 
void Parsing_Info_Str(vector<string> Info, vector<int> Group_Info[4][3][3][3])
{
    for (int i = 0; i < Info.size(); i++)
    {
        int Idx = 0;
        string Temp = "";
        string Score = "";
        while (Idx < Info[i].length())
        {
            Score = "";
            Temp += Info[i][Idx];
            while (Idx < Info[i].length() && Info[i][Idx] != ' ')
            {
                Score += Info[i][Idx];
                Idx++;
            }
            Idx++;
        }
        Mapping_Group_Info(Group_Info, Temp, Score);
     }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    sort(Group_Info[i][j][k][l].begin(), Group_Info[i][j][k][l].end());
                }
            }
        }
    }
}
 
void Mapping_Query_To_Info(vector<int> Group_Info[4][3][3][3], string State, string Score, vector<int> &answer)
{
    int L = Check_State(1, State[0]);
    int W = Check_State(2, State[1]);
    int C = Check_State(3, State[2]);
    int F = Check_State(4, State[3]);
 
    int Group_Num = Group_Info[L][W][C][F].size();
    int Find_Score = stoi(Score);
    int Cnt = 0;
    for (int i = 0; i < Group_Num; i++)
    {
        if (Group_Info[L][W][C][F][i] >= Find_Score) break;
        Cnt++;
    }
    answer.push_back(Group_Num - Cnt);
}
 
void Parsing_Query_Str(vector<string> query, vector<int> Group_Info[4][3][3][3], vector<int> &answer)
{
    for (int i = 0; i < query.size(); i++)
    {
        int Idx = 0;
        string Temp = "";
        while (Idx < query[i].length())
        {
            Temp += query[i][Idx];
            while (Idx < query[i].length() && query[i][Idx] != ' ')
            {
                Idx++;
            }
            if ('1' <= query[i][Idx + 1] && query[i][Idx + 1] <= '9') break;
            Idx += 5;
        }
        string Score = "";
        Idx++;
        while (Idx < query[i].length())
        {
            Score += query[i][Idx];
            Idx++;
        }
        Mapping_Query_To_Info(Group_Info, Temp, Score, answer);
    }
}
 
vector<int> solution(vector<string> info, vector<string> query) 
{
    vector<int> answer;
    vector<int> Group_Info[4][3][3][3];
    Parsing_Info_Str(info, Group_Info);
    Parsing_Query_Str(query, Group_Info, answer);
    return answer;
}
출처: https://yabmoons.tistory.com/621 [얍문's Coding World..:티스토리]
