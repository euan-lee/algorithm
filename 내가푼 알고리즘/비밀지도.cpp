#include <string>
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;

string to_binary(int number,int n){
    string bit_string="";
    int cnt=0;
    while(cnt<n){
        cnt++;
        bit_string=to_string(number%2)+bit_string;
        number=number/2;
    }
    printf("%s\n",bit_string.c_str());
    return bit_string;     
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    vector<string> temp1;
    vector<string> temp2;
    for(int i=0;i<n;i++){
        temp1.push_back(to_binary(arr1[i],n));
        temp2.push_back(to_binary(arr2[i],n));
        printf("\n");
    }
    for(int i=0;i<n;i++){
        string temp="";
        for(int j=0;j<n;j++){
            if(temp1[i][j]=='1'||temp2[i][j]=='1'){
                temp=temp+"#";
            }
            else{
            temp=temp+" ";
            }
        }    
    printf("temp:%s\n",temp.c_str());  
    answer.push_back(temp);
    }
    return answer;
}
