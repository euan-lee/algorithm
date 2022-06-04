
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int answer = 50;
bool visited[50];

//다른 문자가 1개인지 확인하는 함수
bool check_diff(string a, string b){
  int dif_cnt =0;

  for(int i=0; i<a.size();i++){
    if(a[i]!=b[i]){
      dif_cnt++;
    }
  }
  // 다른 문자가 1개일때
  if(dif_cnt==1){
    return true;
  }
  // 다른문자가 한개가 아닐때
  return false;
}

void dfs(string begin, string target,vector<string>words,int step){
  // step이 이전에 찾은 answer보다 크면 탐색할 필요가 없다
  if(answer <= step)
    return;

  if(begin==target){
    answer = min(answer,step);
    return;
  }
  
  for(int i=0; i<words.size();i++){
    // 한개의 문자만 다르고 방문 하지 않은 단어이면 탐색 시작
    if(check_diff(begin,words[i]) && !visited[i]){
      visited[i]=true;
      // 그 단어부터 탐색을 다시 시작한다. 단계가 하나 추가되었으므로 step+1을 인자로 넘긴다.
      dfs(words[i],target,words,step+1);
      // dfs 재귀 호출하여 종료되어 여기로 돌아오면, 백트래킹 (방문 표시 해제) 하여 다음분기점부터 다시 탐색을 시작한다.
      visited[i]=false;
    }
  }
  
  return;
}

int solution(string begin, string target, vector<string> words) {
  dfs(begin,target,words,0);

  // 탐색후 target문자열을 만나지 못했을 때
  if(answer == 50)
    return 0;

  return answer;
}
