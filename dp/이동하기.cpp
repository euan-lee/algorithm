#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

using namespace std;

#define MAX 1001

int N, M;
int arr[MAX][MAX] = { 0, };
int copy_arr[MAX][MAX];

int DP() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int compare_number = 0;
			compare_number = max(copy_arr[i - 1][j - 1], max(copy_arr[i - 1][j], copy_arr[i][j - 1]));
			copy_arr[i][j] = compare_number + arr[i][j];
		}
	}
	return copy_arr[N][M];
}

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
}

int main() {
	init();
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> arr[i][j];
	
	cout << DP() << endl;
	return 0;
}