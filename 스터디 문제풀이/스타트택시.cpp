#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

struct taxi {
	int r, c, fuel;
	//지금 위치랑 연료!
};
struct customer {
	int start_r, start_c;
	int end_r, end_c;
};

int d_r[4] = { 1,-1,0,0 };
int d_c[4] = { 0,0,1,-1 };

taxi me;
vector<customer> customers;
int how_far = 987654321;
int go_to;

int n, m;
int map[21][21];
int visited[21][21];
int flag = 0;

int bfs(int new_r, int new_c)//me 에서부터 목적지!
{
	memset(visited, 0, sizeof(visited));

	if (me.r == new_r && me.c == new_c)//목적지랑 지금위치랑 똑같을때!!
	{
		return 0;
	}

	visited[me.r][me.c] = 1;
	queue<pair<int, int> > q;
	q.push(make_pair(me.r, me.c));

	int result = 0;
	while (!q.empty())
	{
		int s = q.size();
		for (int j = 0; j < s; j++)
		{
			int r = q.front().first;
			int c = q.front().second;
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int new_rr = r + d_r[i];
				int new_cc = c + d_c[i];
				if (new_rr <= 0 || new_cc <= 0 || new_rr > n || new_cc > n)
					continue;
				if (visited[new_rr][new_cc] == 1)
					continue;
				if (map[new_rr][new_cc] == 1)//벽
					continue;

				if (new_rr == new_r && new_cc == new_c)//목적지
					return result + 1;

				visited[new_rr][new_cc] = 1;
				q.push(make_pair(new_rr, new_cc));
			}

		}
		result++;
	}

	return -1;//갈수 없는 경우
}

void find_shortest()
{

	for (int i = 0; i < customers.size(); i++)
	{
		int sum = bfs(customers[i].start_r, customers[i].start_c);
		if (sum == -1)//갈수 없음!!
		{
			flag = 1;
			return;
		}
		else if (how_far > sum)
		{
			//더 짧으면
			how_far = sum;
			go_to = i;
		}
		else if (how_far == sum)
		{
			if (customers[go_to].start_r > customers[i].start_r)
			{
				go_to = i;
			}
			else if (customers[go_to].start_r == customers[i].start_r)
			{
				if (customers[go_to].start_c > customers[i].start_c)
					go_to = i;
			}
		}
	}
}

int main()
{
	cin >> n >> m >> me.fuel;

	for(int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++)
		{
			cin >> map[i][j];//1이 벽
		}
	cin >> me.r >> me.c;
	for (int i = 0; i < m; i++)
	{
		customer a;
		cin >> a.start_r >> a.start_c >> a.end_r >> a.end_c;
		customers.push_back(a);
	}

	while (true)//연료 떨어지거나, 모두 다 채웠으면 나갈꺼임
	{
		how_far = 987654321;
		find_shortest();
		//손님까지의 거리 how_far
		//어디 손님? go_to

		if (flag == -1)//갈수 없는 곳이 있음!!
		{
			cout << -1 << endl;
			return 0;
		}

		if (me.fuel < go_to)//가야되는 거리보다 연료가 더 많이 필요
		{
			cout << -1 << endl;
			return 0;
		}

		me.fuel = me.fuel - how_far;

		me.r = customers[go_to].start_r;
		me.c = customers[go_to].start_c;


		how_far = 987654321;
		how_far = bfs(customers[go_to].end_r, customers[go_to].end_c);

		if (how_far == -1)//갈수 없는 길이면!
		{
			cout << -1 << endl;
			return 0;

		}
		if (how_far > me.fuel)
		{
			//목적지까지 못가여...ㅜㅜ
			cout << -1 << endl;
			return 0;
		}
		//무사히 대려다줌
		me.fuel = me.fuel - how_far;
		me.r = customers[go_to].end_r;
		me.c = customers[go_to].end_c;
		customers.erase(customers.begin() + go_to);

		

		me.fuel += how_far * 2;
		if (customers.size() == 0)//한번은 무조건 하니까 조건 뒤에 해도 됨염
			break;
	}

	cout << me.fuel << endl;
	return 0;
}
