#include <vector>
#include <set>
#include <algorithm>
 
using namespace std;
 
bool compare(pair<int,int> a, pair<int,int> b)
{
    if (a.second < b.second) return true;
    else return false;
}
 
int solution(int n, int m, vector<vector<int>> timetable) 
{
    int answer = 0;
    
    // find maxPeople
    int maxPeople = 0;
    vector<pair<int, int>> timetable2;
 
    for (int i = 0; i < m; i++)
        timetable2.push_back({ timetable[i][0], timetable[i][1] });
 
    sort(timetable2.begin(), timetable2.end(), compare);
 
    for (int i = 0; i < m; i++)
    {
        int tempMax = 1;
        for (int target = i + 1; target < m; target++)
        {
            if (timetable2[i].second >= timetable2[target].first &&
                timetable2[i].second <= timetable2[target].second)
                tempMax++;
        }
        maxPeople = maxPeople > tempMax ? maxPeople : tempMax;
    }
    // if people == 1 then return 0
    if (maxPeople == 1) return 0;
    // 
    for (int dis = 2 * n - 2; dis > 0; dis--)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                set<pair<int, int>> canMove;
                canMove.insert({ i, j });
                int tempPeople = 1;
 
                for (int y = i; y < n; y++)
                {
                    for (int x = 0; x < n; x++)
                    {
                        if (y < i || (y == i && x <= j)) continue;
 
                        set<pair<int, int>>::iterator iter;
                        for (iter = canMove.begin(); iter != canMove.end(); iter++)
                        {
                            int distance = abs(y - (*iter).first) + abs(x - (*iter).second);
                            if (distance < dis) break;
                        }
 
                        if (iter == canMove.end())
                        {
                            canMove.insert({ y, x });
                            tempPeople++;
                        }
 
                        if (tempPeople == maxPeople)
                        {
                            answer = dis;
                            return answer;
                        }
                    }
                }
            }
        }    
    }
    
    return answer;
}
