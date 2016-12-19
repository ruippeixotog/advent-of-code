#include <cstdio>

#define N 3001330

bool out[N];

int next(int curr) {
  do { curr = (curr + 1) % N; } while(out[curr]);
  return curr;
}

int main() {
  int across = N / 2, count = N;
  while(count > 1) {
    out[across] = true;
    across = next(across);
    if(count % 2 == 1) across = next(across);
    count--;
  }
  printf("%d\n", across + 1);
  return 0;
}
