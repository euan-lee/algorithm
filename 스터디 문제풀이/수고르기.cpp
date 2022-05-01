#include <iostream>
#include <algorithm>
using namespace std;
long long arr[100000];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int num;
	long long limit;
	cin >> num >> limit;
	for (int i = 0; i < num; i++)
		cin >> arr[i];
	sort(arr, arr + num);
	int r = 0, l = 0;
	long long diff = 0, result = 2000000001;
	while (l <= r && r < num) {
		if (diff >= limit) {
			result = min(result, diff);
			if (l == r) {
				r++;
				if (r == num) break;
				diff = arr[r] - arr[l];
			}
			else {
				l++;
				diff = arr[r] - arr[l];
			}
		}
		else {
			r++;
			if (r == num) break;
			diff = arr[r] - arr[l];
		}
	}
	cout << result;
	system("pause");
	return 0;
}
