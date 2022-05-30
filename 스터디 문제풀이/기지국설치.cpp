#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int solution(int n, vector<int> stations, int w)
{
    int answer=0;
    int now =1;
    int station_index =0;
    while(now<=n)
    {
        //현재 위치가 범위 안이라면
        if(now >= stations[station_index]-w && now <= stations[station_index]+w)
        {
            now = stations[station_index]+w;
            station_index++;
        }
        else//기지국 새로 설치!
        {
            answer++;
            now += w*2;
        }
        //다음칸으로~
        now++;
    }
    
    return answer;
}

