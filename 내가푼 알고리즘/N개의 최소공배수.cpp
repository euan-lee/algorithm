#include <string>
#include <vector>
#include <stack>
using namespace std;

int gcd(int a, int b){
	while(b!=0){
		int r = a%b;
		a= b;
		b= r;
	}
	return a;
}

int lcm(int a, int b){
    return a * b / gcd(a,b);
}


int solution(vector<int> arr) {
    int answer = 0;
    stack<int> s;
    for(int i=0;i<arr.size();i++){
        s.push(arr[i]);
    }
    int cnt=0;
    int num=arr.size();
    int x;
    int y;
    int z;
    while(cnt<num-1){
        x=s.top();
	    s.pop();
        y=s.top();
	    s.pop();
        z=lcm(x,y);
       // printf("x:%d y:%d z:%d\n",x,y,z);
        s.push(z);
        cnt++;
    }
    
    answer=s.top();
    return answer;
}
