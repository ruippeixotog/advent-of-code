#include <cstdio>

int main() {
  int step; scanf("%d\n", &step);

  int bufSize = 1, pos = 0, atPos1 = -1;
  for(int k = 1; k <= 50000000; k++) {
    pos = ((pos + step) % bufSize) + 1;
    if(pos == 1) atPos1 = k;
    bufSize++;
  }
  printf("%d\n", atPos1);
  return 0;
}
