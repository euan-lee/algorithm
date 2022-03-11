#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <list>
#include <utility>
#include <functional>
#define MAX 1005
#define INF 987654321
#define MOD 1000000
#pragma warning(disable:4996)
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;

int n, x, y, a, b;
ll from[5], to[5];
int dy[5] = { 0,1,0,-1,0 }, dx[5] = {0,0,1,0,-1};

int main()
{
	scanf("%d%d%d", &n, &x, &y);

	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &a, &b);
		//printf("<%d %d %d %d>\n", x, y, a, b);
		for (int p = 0; p < 5; p++)
		{
			for (int q = 0; q < 5; q++)
			{
				//printf("-1");
				int tmp= abs((y + dy[p]) - (b + dy[q])) + abs((x + dx[p]) - (a + dx[q]));
				//printf("-2");
				if (p == 0)
				{
					to[q] = tmp+from[p];
					continue;
				}
				if (to[q] > tmp+from[p])
					to[q] = tmp+from[p];
			}
			if (i == 0)
				break;
		}
		swap(from, to);
		x = a, y = b;
	}
	ll ans = from[0];
	for (int i = 1; i < 5; i++)
		ans = min(ans, from[i]);
	printf("%lld", ans);
	return 0;
}
