#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
vector<int> psum(100001); //누적합
vector<int> here_max(100001); //현재 위치에서의 최댓값
vector<int> gold(100001); //보석의 가치

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;

	psum[0] = 0;
	here_max[0] = 0;
	gold[0] = 0;

	for (int i = 1; i <= n; i++)
	{
		int input;
		cin >> input;

		psum[i] = psum[i - 1] + input; //누적합 저장
		gold[i] = input;
	}

	here_max[m] = psum[m]; //보석을 줍는다면 m개 이상은 주어야 한다
	for (int i = m + 1; i <= n; i++)
	{
		here_max[i] = max(here_max[i - 1] + gold[i], psum[i] - psum[i - m]); //그 전 위치(i-1)에서 보석 줍기가 끝나는 최댓값 + 현재 보석(gold[i]) 과 현재 위치에서 끝나는 m개의 보석줍기(psum[i] - psum[i-m]) 중 값이 더 큰것이 현재위치에서 보석 줍기가 끝날때 최댓값이다.
	}

	int result = -987654321;
	for (int i = m; i <= n; i++)
	{
		result = max(result, here_max[i]);
	}

	if (result < 0) //보석을 안줍는게 가치가 더 클때
		result = 0;

	cout << result;

	return 0;
}
