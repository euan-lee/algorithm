#include <string>
#include <vector>
using namespace std;


int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    int skill_index=0;
    for(int i=0;i<skill_trees.size();i++){
        vector<int> skill_num;
        for(int j=0;j<skill_trees[i].size();j++){
            for(int k=0;k<skill.size();k++){
                if(skill_trees[i][j]==skill[k]){
                    skill_num.push_back(k);
                }    
            }
        //    printf("%s\n",skill.c_str());
        }    
        printf("skill tree:%s\n",skill_trees[i].c_str()); 
        int cnt=0;
        for(int i=0;i<skill_num.size();i++){
            if(skill_num[i]==i){
                cnt++;
            }
            printf("skillnum:%d\n",skill_num[i]);
        }
        if(cnt==skill_num.size()){
            answer++;
        }
    }
    return answer;
}
