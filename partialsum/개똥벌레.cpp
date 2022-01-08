#include<iostream>
#include<algorithm>
using namespace std;

int N, H, h;
long long stalagmite[500001], stalactite[500001]; // 석순 ,종유석
long long sum[500001];

int main() 
{
	ios::sync_with_stdio(0); 
	cin.tie(0); 

	cin >> N >> H;

	for (int i = 1; i <= N; i++)
	{
		cin >> h;
		if (i % 2 == 1) // 석순
		{
			stalagmite[h]++;
		}
		else // 종유석
		{
			stalactite[h]++;
		}
	}

	for (int i = H - 2; i >= 1; i--) // 석순, 종유석 누적 합
	{
		stalagmite[i] += stalagmite[i + 1];
		stalactite[i] += stalactite[i + 1];
	}

	sum[1] = stalagmite[1];
	sum[H] = stalactite[1];

	for (int i = 2; i <= H - 1; i++)
	{
		sum[i] = stalagmite[i] + stalactite[H + 1 - i];
	}

	/*
	for (int i = H; i >= 1; i--)
	{
		cout << "높이 "<<i <<"일때 파괴하는 장애물 수 : " << sum[i] << endl;
	}
	*/
	
	sort(sum + 1, sum + H + 1);

	cout << sum[1] << " ";
	cout << upper_bound(sum + 1, sum + H + 1, sum[1]) - lower_bound(sum + 1, sum + H + 1, sum[1]);
}
