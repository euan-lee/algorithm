#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int N;
    cin >> N;
    
    vector<int> v(N);
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }
    
    int result = 0;
    sort(v.begin(), v.end());
    do{
        int temp = 0;
        for(int i = 0; i < v.size() - 1; i++)
            temp += abs(v[i] - v[i+1]);
        
        result = max(result, temp);
    }while(next_permutation(v.begin(), v.end()));
    
    cout << result << '\n';
    
    return 0;
}
