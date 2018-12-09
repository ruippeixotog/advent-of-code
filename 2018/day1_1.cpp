#include <cstdio>

int main() {
  int sum = 0;
  char sign; int val;
  while(scanf("%c%d\n", &sign, &val) == 2) {
    sum += (sign == '+' ? 1 : -1) * val;
  }
  printf("%d\n", sum);
  return 0;
}
