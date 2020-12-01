#include <cstdio>

#define MAXN 2000

int n = 0, entries[MAXN];

int main() {
  int entry;
  while(scanf("%d\n", &entry) > 0) {
    entries[n++] = entry;
  }
  int res1 = -1, res2 = -1;
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      if(entries[i] + entries[j] == 2020) {
        res1 = entries[i] * entries[j];
      }
      for(int k = j + 1; k < n; k++) {
        if(entries[i] + entries[j] + entries[k] == 2020) {
          res2 = entries[i] * entries[j] * entries[k];
        }
      }
    }
  }
  printf("%d %d\n", res1, res2);
  return 0;
}
