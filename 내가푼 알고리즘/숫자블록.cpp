#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<int> solution(long long begin, long long end) {
    vector<int> answer;
    for(int num = begin; num <= end; ++num){
        if (num == 1){
            answer.push_back(0);
            continue;
        }
        bool found = false;
        // 1️⃣ 처음으로 num % i == 0 가 되는 경우 -> i 는 가장 작은 약수. 고로 num / i 는 자기 자신을 제외한 가장 큰 약수가 된다. (i 의 짝꿍 약수)
        // 2️⃣ 만약 num / i 가 (자기 자신 제외 가장 큰 약수) 10,000,000 을 넘는다면 자연스럽게 다음 반복을 통해 더 커진, 증가된 i 부터 검사해나가면 된다. i 가 증가하면 num / i 는 감소한다. 이렇게 10,000,000 을 넘지 않는 선에서의! 가장 큰 약수를 구하면 된다.(num/i 가 10,000,000 을 넘지 않으면서 동시에 약수가 최는 최초의 수)
        for (int i = 2; i <= sqrt(num); ++i){
            if (num % i == 0 && num / i <= 10000000){
                answer.push_back(num / i);
                found = true;
                break;
            }
        }
        // 소수이거나 
        // sqrt(num)이하 약수의 짝꿍들이 모두 10,000,000 보다 큰 수 
        // 즉, 위 for문의 if 에 한번도 걸린적이 없음
        if (!found) 
            answer.push_back(1);
    }
    return answer;
}
