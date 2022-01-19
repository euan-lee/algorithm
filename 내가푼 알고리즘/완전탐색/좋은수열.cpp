#include <cstdio>
#include <algorithm> 
using namespace std; 
int N, arr[80]; 
void algo(int cnt) { 
  for (int i = 1; i <= cnt / 2; i++) { 
    if (equal(arr + cnt - i, arr + cnt, arr + cnt - i * 2)) return;
  } 
  if (cnt == N) {
    for (int i = 0; i < N; i++) printf("%d", arr[i]);
    exit(0); 
  } 
  for (int i = 1; i <= 3; i++) { 
    arr[cnt] = i; 
    algo(cnt + 1); 
  }
} 
int main() {
  scanf("%d", &N); 
  algo(0);
  return 0;
}
