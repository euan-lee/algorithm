#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

int n;
vector<string> board;
int result = 987654321;

int Solve(int row_status)
{
	int ret = 0;
	for (int j = 0; j < n; j++)
	{
		int h_cnt = 0; //해당 행에서 앞면의 개수
		int t_cnt = 0; //해당 행에서 뒷면의 개수

		for (int i = 0; i < n; i++)
		{
			//해당 행이 뒤집혀 있을 경우
			if (((row_status >> i) & 1) == 1)
			{
				if (board[i][j] == 'H')
					t_cnt++;
				else
					h_cnt++;
			}

			else
			{
				if (board[i][j] == 'H')
					h_cnt++;
				else
					t_cnt++;
			}
		}

		//j열에서 앞면의 개수와 뒷면의 개수중 작은것을 더하면 된다
		//만약 앞면의 개수가 더 작다면 j열을 뒤집는다고 생각하면 되기 때문이다 
		ret += min(h_cnt, t_cnt);
	}

	return ret;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string input;
		cin >> input;

		board.push_back(input);
	}

	//각 행들의 뒤집힌 경우를 모두 확인한다
	for (int row_status = 0; row_status < (1 << n) - 1; row_status++)
	{
		result = min(result, Solve(row_status));
	}

	cout << result;

	return 0;
}
