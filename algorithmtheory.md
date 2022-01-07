알고리즘

-dp:dynamic programming의 약자로 큰 문제를 한 번에 해결하기 힘들 때 작은 여러 개의 문제로 나누어서 푸는 기법이다.(점화식),크게 두가지로 풀수 있고 memoizationtop-down)과 (bottom-up)approach가 있다.

top-down의 예시

```c++
int fiboData[100] = {0,};

int fibo(int n)
{
  if (n<=2) 
    return 1;
  if (fiboData[n]==0)
    fiboData[n] = fibo(n-1) + fibo(n-2);
  return fiboData[n];
}
```

bottom-up approach

```c++
int fibo(int n)
{
  fibodata[0] = 0;
  fiboData[1] = 1;
  for (int i=2; i<=n; i++)
    fiboData[i] = fiboData[i - 1] + fiboData[i - 2];
  return fiboData[n];
}

```

