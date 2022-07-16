#include <string>
#include <vector>

using namespace std;


string ChangeSystem(int num,int n){
	string make_base = "";
    string temp = "";
    for(int i=num;i>0;){
        if(i%n==10)temp="A";
        else if(i%n==11)temp="B";
        else if(i%n==12)temp="C";
        else if(i%n==13)temp="D";
        else if(i%n==14)temp="E";
        else if(i%n==15)temp="F";
        else temp=to_string(i % n);
    	make_base = temp + make_base;
        i /= n;
    }
    
    return make_base;
}

string solution(int n, int t, int m, int p) {
    string answer="";
    string contain="0";
    
    //for문 순회 얼마만큼??
    for(int i=1;i<t*m;i++){
        contain=contain+ChangeSystem(i,n);
    }
    
    //n진법으로 전환
    for(long long i=p-1;i/m<t;i=i+m){
        printf("%c",contain[i]);
        answer.push_back(contain[i]);
    }
    return answer;
}
