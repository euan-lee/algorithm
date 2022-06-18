#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int N=brown+yellow;
    int width=0;
    int height=0;
	for (int i=1;i<=N;i++){
		if (N%i==0){
            width=i;
            height=N/width;
            if(width>=height){   
                if((width-2)*(height-2)==yellow){
                    answer.push_back(width);
                    answer.push_back(height);
                    printf("width:%d\n",width);
                    printf("height:%d\n",height);
                }
            }
        }   
    }
    return answer;
}
