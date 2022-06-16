#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    map<string, int> m;
    int cnt=0;
    char prev=words[0][0];
    int circle=0;
    for(int i=0;i<words.size();i++){
        if(cnt%n==0){
            circle++;
        }
        cnt++;
        int talk_person=0;
        talk_person=cnt%n;
        if(talk_person==0){
                talk_person=n;
        }
        printf("cnt:%d\n",cnt);
        printf("circle:%d\n",circle);
        if(prev==words[i][0]&&m.find(words[i])==m.end()){
            m.insert({words[i],talk_person});
            prev=words[i].back();
        }
        else if(prev==words[i][0]&&m.find(words[i])!=m.end()){
        printf("ans \n");
            for (auto iter = m.begin();iter!=m.end();iter++){
                 if(words[i]==iter->first){
                     printf("talk_person %d\n",talk_person);
                     printf("circle:%d\n",circle);
                     answer.push_back(talk_person);    
                     answer.push_back(circle);
                 }
            }
          return answer;
        }
        else if(prev!=words[i][0]&&m.find(words[i])==m.end()){
            answer.push_back(talk_person);    
            answer.push_back(circle);
            return answer;
        }
        
    }
    answer.push_back(0);
    answer.push_back(0);
    return answer;
}
