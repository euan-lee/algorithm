#include <string>
#include <vector>
using namespace std;

int total;
int answer;
int cnt;
void Go(string ans,string word){
    string temp[6] = {"A","E","I","O","U"};
  //  printf("%s %d\n",ans.c_str(),answer);
    if(ans.compare(word)==0){ 
        printf("hello\n");
        answer=cnt;
    printf("ans is!!:%d\n",answer);
        return ;
    }
    
	if (ans.length()==5)
		return ;
    for(int i=0;i<5;i++){
         cnt++;
        Go(ans+temp[i],word);
    }
}

int solution(string word) {
    answer=0;
    Go("",word);
    return answer;
}
