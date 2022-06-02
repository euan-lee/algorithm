#include <iostream>
#include <vector>
#include<string>
using namespace std;

#define N 26

int main(int argc, char**argv) {
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	vector<int> ans(N);
	string str="";
	
	cin >> str;
	

	for(int i=0; i<str.size(); i++){
		ans[str.at(i)-97]++;
	}
	
		
	for(int i=0; i<N; i++){
		cout << ans[i] <<" ";
	}
	
	return 0;
}
