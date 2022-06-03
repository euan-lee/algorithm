#include <string>

#include <vector>

#include <map>

 

using namespace std;

 

vector<int> solution(int n, vector<string> words) {

    map<string, int> word;

    word[words[0]]++;

    for(int i=1; i<words.size(); i++){

        if(word[words[i]] || words[i].front() != words[i-1].back())

            return {(i%n)+1,(i/n)+1};

        word[words[i]]++;

    }

    return {0, 0};

}
