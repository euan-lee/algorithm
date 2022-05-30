#include <cstdio>
#include <cstring>
using namespace std;

int dp_table[1001][1001];
int n, k;

int dp(int cur, int x)
{
	if (cur <= 0 || cur < 2 * x) return 0;
	if (x == 1)	return cur;

	int &cache = dp_table[cur][x];
	if (cache != -1)	return dp_table[cur][x];

	return cache = (dp(cur - 2, x - 1) + dp(cur - 1, x)) % 1000000003;

}

int main() 
{
	scanf("%d", &n);
	scanf("%d", &k);
	memset(dp_table, -1, sizeof(dp_table));

	printf("%d", dp(n, k));
	return 0;
}
