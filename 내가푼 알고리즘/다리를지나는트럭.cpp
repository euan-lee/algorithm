#include <queue>
#include <vector>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    
    int idx=0;    //차량 지목용 idx
    int sum=0;   //현재 다리에 올라와있는 차량 무게 총합
    queue<int> q;  //현재 다리를 건너는 트럭 체크용 큐
    
    while(1){
        
        if(idx == truck_weights.size()){  //마지막 트럭일 때
            answer += bridge_length;  //마지막 트럭이 지나는 시간 추가
            break;  
        }
        
        answer++; //시간초 증가
        int tmp = truck_weights[idx];
        
        //차가 다리를 다 건넜을 경우
        if(q.size() == bridge_length){
            sum -= q.front();  //다 건넜으니 현재 다리에 있는 차들의 무게에서 제외
            q.pop();  
        }
        
        if(sum + tmp <= weight){  //다리에 다음 차가 진입할 수 있다면
            sum += tmp;  //차량 무게 추가
            q.push(tmp);  
            idx++;  //다음 차량을 위해서
        }else{   
            q.push(0);  //진입할 수 없다면 0을 푸시해서 시간초 계산
        }
    }
   
    return answer;
}
