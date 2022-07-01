#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(int cacheSize, vector<string> cities) {
    unordered_map<string,int> table;
     int answer = 0;
    for(int i=1;i<=cities.size();i++){
        string city_name=cities[i-1];
        for(int i=0;i<city_name.size();i++){
            city_name[i]=tolower(city_name[i]);
        }
        if(table.find(city_name)!=table.end()){
            if((i-table[city_name])>cacheSize){
                answer=answer+5;
                table.erase(city_name);
                table.insert({city_name,i});
            }
            else{
                answer=answer+1;
                table.erase(city_name);
                table.insert({city_name,i});
            }
        }
        else{
            table.insert({city_name,i});
            answer=answer+5;
        }
    }   
    return answer;
}
