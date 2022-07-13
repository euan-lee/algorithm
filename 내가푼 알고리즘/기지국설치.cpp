#include <vector>
using namespace std;
 
int Install(int Start, int End, int W)
{
    int Install_Range = End - Start + 1;
    int Cover_Range = W * 2 + 1;
 
    if (Install_Range <= 0) return 0;
    if (Install_Range % Cover_Range == 0) return Install_Range / Cover_Range;
    return (Install_Range / Cover_Range) + 1;
}
 
int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
 
    for (int i = 0; i < stations.size(); i++)
    {
        if (i == 0) answer = answer + Install(1, stations[i] - w - 1, w);
        else answer = answer + Install(stations[i - 1] + w + 1, stations[i] - w - 1, w);
    }
    answer = answer + Install(stations[stations.size() - 1] + w + 1, n, w);
 
    return answer;
}

