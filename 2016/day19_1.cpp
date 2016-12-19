#include <cstdio>

#define N 3001330

int main() {
  int first = 1, count = N, step = 1;
  while(count > 1) {
    if(count % 2 == 1) first += step * 2;
    count /= 2;
    step *= 2;
  }
  printf("%d\n", first);
  return 0;
}
