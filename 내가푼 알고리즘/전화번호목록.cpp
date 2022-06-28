#include <string>
#include <vector>
#include<unordered_map>
using namespace std;

bool solution(vector<string> phone_book) {
    unordered_map<string,int> table;
    
    for(int i=0;i<phone_book.size();i++){
        table.insert({phone_book[i],1});
    }
    
      for(int i=0;i<phone_book.size();i++){
          string temp="";
            for(int j=0;j<phone_book[i].size();j++){
                temp=temp+phone_book[i][j];
                if(table[temp]&&temp!=phone_book[i])
                    return false;
            }
      }
    return true;
}
