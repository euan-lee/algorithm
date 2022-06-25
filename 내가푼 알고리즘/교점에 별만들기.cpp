#include <string>
#include <vector>
using namespace std;


vector<string> solution(vector<vector<int>> line) {
    vector<pair<long,long> > cord;
    vector<string> answer;
    long long x=0;
    long long y=0;
    long long min_y=10000000001;
    long long max_y=-10000000001;
    long long max_x=-10000000001;
    long long min_x=10000000001;
    long long son1=0;
    long long mother1=0; 
    long long son2=0;
    for(int i=0;i<line.size();i++){
        for(int j=i+1;j<line.size();j++){
            son1=(long long)line[i][1]*line[j][2]-(long long)line[i][2]*line[j][1];
            mother1=(long long)line[i][0]*line[j][1]-(long long)line[i][1]*line[j][0];
            son2=(long long)line[i][2]*line[j][0]-(long long)line[i][0]*line[j][2];
            if(mother1==0)continue;
            if(son1%mother1!=0||son2%mother1!=0)continue;
            x=(son1/mother1);
            y=(son2/mother1);
            min_y=min(y,min_y);
            max_y=max(y,max_y);
            min_x=min(x,min_x);
            max_x=max(x,max_x);
            cord.push_back(pair<long,long>(x,y));     
        }    
    }
    long long row = max_y-min_y+1;
    long long col = max_x-min_x+1;
    string temp(col, '.');
    answer.assign(row, temp);
    for(int i=0;i<cord.size();i++){
         x=cord[i].first;
         y=cord[i].second;
        answer[max_y-y][x-min_x]='*';
    }
    return answer;
}
