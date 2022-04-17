#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

string solution(string m, vector<string> musicinfos)
{
    string answer = "";
    vector<vector<string>> infos(musicinfos.size());
    for (int i = 0; i < musicinfos.size(); i++)
    {
        stringstream ss(musicinfos[i]);
        string temp;
        while (getline(ss, temp, ','))
            infos[i].push_back(temp);
    }
    for (int i = 0; i < infos.size(); i++)
    {
        for (int j = 0; j < infos[i][3].size();)
        {
            if (infos[i][3][j + 1] == '#')
            {
                infos[i][3][j] += 10;
                infos[i][3].erase(infos[i][3].begin() + j + 1);
            }
            else
                j++;
        }
    }
    for (int i = 0; i < m.size();)
    {
        if (m[i + 1] == '#')
        {
            m[i] += 10;
            m.erase(m.begin() + i + 1);
        }
        else
            i++;
    }
    vector<int> times;
    for (int i = 0; i < infos.size(); i++)
    {
        stringstream ss1(infos[i][0]);
        stringstream ss2(infos[i][1]);
        int t1 = 0;
        int t2 = 0;
        string temp1;
        string temp2;
        while (getline(ss1, temp1, ':'))
            t1 = (t1 * 60) + stoi(temp1);
        while (getline(ss2, temp2, ':'))
            t2 = (t2 * 60) + stoi(temp2);
        times.push_back(abs(t2 - t1));
    }
    vector<string> temp(infos.size());
    for (int i = 0; i < infos.size(); i++)
    {
        for (int j = 0; j < times[i]; j++)
        {
            temp[i].push_back(infos[i][3][j % (infos[i][3].size())]);
        }
    }
    int max = 0;
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i].find(m) != string::npos && times[i] > max)
        {
            max = times[i];
            answer = infos[i][2];
        }
    }
    if (answer == "")
        answer = "(None)";
    return answer;
}
