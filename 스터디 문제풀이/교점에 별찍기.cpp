#include <string>
#include <vector>
#include <iostream>

using namespace std;


vector<string> solution(vector<vector<int>> line) {
    vector<string> answer;
    
    vector<vector<long long>> result;
    
    long long minX=10000000001;
    long long minY=10000000001;
    long long maxX=-10000000001;
    long long maxY=-10000000001;
        
    
    for(int i=0; i < line.size(); i++){        
        long long standardX = line[i][0];
        long long standardY = line[i][1];
        long long standardNum = line[i][2];
        for(int k=i+1; k < line.size(); k++){
            long long nowX = line[k][0];
            long long nowY = line[k][1];
            long long nowNum = line[k][2];
            
            long long check=0;
            long long getX=0;
            long long getY=0;  
            long long under = (standardX*nowY) - (standardY*nowX);            
            long long up = (standardY*nowNum) - (standardNum*nowY);            
            if(0==under){
                continue;
            }
            
            if((0 != under) && (0 != up)){
                check = up % under;
                if(0 != check){
                    continue;
                }
                getX = up/under;
            }                        
                      
            up = (standardNum*nowX) - (standardX*nowNum);
            if((0 != under) && (0 != up)){
                check = up % under;
                if(0 != check){
                    continue;
                }
                getY = up/under;
            }            
            vector<long long> temp = {getX, getY};            
            result.push_back(temp);         
            if(minX > getX){
                minX=getX;
            }            
            if(minY > getY){
                minY=getY;
            }
            if(maxX < getX){
                maxX = getX;
            }
            if(maxY < getY){
                maxY = getY;
            }
        }
    } 
        
    long long mapX = maxX - minX+1;
    long long mapY = maxY - minY+1;  
    
    string mapTemp(mapX, '.');    
    answer.assign(mapY, mapTemp);
    
    
    for(vector<long long> temp : result){   
        temp[0] = temp[0]+(minX* (-1));
        temp[1] = (temp[1]-maxY) * (-1); 
        answer[temp[1]][temp[0]] = '*';        
    }    
    
    
    return answer;
}
