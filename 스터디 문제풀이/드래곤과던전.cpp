#include <iostream>

#include <algorithm>

#include <climits>

using namespace std;

 

const int MAX = 123456;

 

int N, H;

pair<int, pair<int, int>> room[MAX];

 

bool func(long long mid)

{

        long long hp = mid;

        long long atk = H;

 

        for (int i = 0; i < N; i++)

        {

                 if (room[i].first == 1)

                 {

                         //몬스터보다 먼저 죽을 경우

                         if (((room[i].second.second - 1) / atk) > ((hp - 1) / room[i].second.first))

                                 return false;

                         //몬스터 처치 시 드는 비용

                         hp -= (room[i].second.second - 1) / atk * room[i].second.first;

                 }

                 else

                 {

                         atk += room[i].second.first;

                         hp = min(hp + room[i].second.second, mid);

                 }

        }

        return true;

}

 

int main(void)

{

        ios_base::sync_with_stdio(0);

        cin.tie(0);

        cin >> N >> H;

 

        for (int i = 0; i < N; i++)

                 cin >> room[i].first >> room[i].second.first >> room[i].second.second;

 

        //LLONG_MAX로 둘 경우 overflow 발생

        long long low = 1, high = 1e18;

        long long result = -1;

        while (low <= high)

        {

                 long long mid = (low + high) / 2;

 

                 if (func(mid))

                 {

                         result = mid;

                         high = mid - 1;

                 }

                 else

                         low = mid + 1;

        }

        cout << result << "\n";

        return 0;

}

