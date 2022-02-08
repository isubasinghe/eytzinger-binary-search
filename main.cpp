#include <stdio.h>

#define N ((int)1e5)
#define BLOCK_SIZE 16

alignas(64) int a[N], b[N+1];

int eytzinger_helper(int *arr, int n, int i, int k) {
  if(k <= n) {
    i = eytzinger_helper(arr, n, i, 2*k);
    b[k] = a[i++];
    i = eytzinger_helper(arr, n, i, 2*k + 1);
  }
  return i;
}

int eytzinger(int *arr, int n) {
  return eytzinger_helper(arr, n, 0, 1);
}

int search(int x) {
  int k = 1;
  while(k <= N) {
    __builtin_prefetch(b+k * BLOCK_SIZE);
    k = 2*k + (b[k] < x);
  }
  k >>= __builtin_ffs(~k);
  return b[k];
}

int main() {
    return 0;
}
