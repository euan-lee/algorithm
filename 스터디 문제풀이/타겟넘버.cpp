#include <vector>

using namespace std;

// 전역변수 answer

int answer = 0;

void get_target_number(vector<int> numbers, int target, int sum, int index){

    //종료 조건

    if (index == numbers.size()){

        if (sum == target) {

            answer++;

        }

        // 같지 않을때도 return

        return;

    }

    //종료 조건이 만족되지않으면 계속 탐색

    get_target_number(numbers, target, sum + numbers[index], index + 1);

    get_target_number(numbers, target, sum - numbers[index], index + 1);

    

   

}

int solution(vector<int> numbers, int target) {

    get_target_number(numbers, target, 0, 0);

    return answer;

}
