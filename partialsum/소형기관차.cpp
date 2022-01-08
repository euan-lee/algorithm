#include <iostream>

#include <algorithm>

#include <cstring> //memset

using namespace std;

 

const int MAX = 50000 + 1;

 

int passengerCarNum;

int passengerCar[MAX];

int maxCarry;

int cache[3][MAX]; //몇번째 소형 기차, 현재 객차 번호

 

int maxPassenger(int trainNum, int idx)

{

        //기저 사례 : 소형기차는 0, 1, 2 이렇게 세개이다

        //기저 사례 : 객차 칸 수를 벗어날 경우

        if (trainNum == 3 || idx >= passengerCarNum)

                 return 0;

 

        int &result = cache[trainNum][idx];

        if (result != -1)

                 return result;

 

        result = 0;

        //해당 객차를 끌고 가지 않을 경우

        //해당 객차를 끌고 갈 경우

        if(idx + maxCarry - 1 <= passengerCarNum) //인덱스 범위를 초과해서 런타임에러 뜨는 것 같다

                 result = max(maxPassenger(trainNum, idx + 1), (passengerCar[idx + maxCarry - 1] - passengerCar[idx - 1]) + maxPassenger(trainNum + 1, idx + maxCarry));

        return result;

}

 

int main(void)

{

        cin >> passengerCarNum;

       

        for (int i = 1; i <= passengerCarNum; i++)

        {

                 int temp;

                 cin >> temp;

                 //나중에 구간 내 승객 수 세기 쉽게

                 passengerCar[i] = passengerCar[i - 1] + temp;

        }

 

        cin >> maxCarry;

 

        memset(cache, -1, sizeof(cache));

 

        cout << maxPassenger(0, 1) << endl;

 

        return 0;

}

