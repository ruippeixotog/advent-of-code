#include <cstdio>

int main() {
  int layer, range, severity = 0;
  while(scanf("%d: %d\n", &layer, &range) == 2) {
    int phase = layer % ((range - 1) * 2);
    if(!phase) severity += layer * range;
  }
  printf("%d\n", severity);
  return 0;
}
