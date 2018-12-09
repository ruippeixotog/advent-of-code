#include <cstdio>

#define MAXN 1000

int fabric[MAXN][MAXN];

int main() {
  int left, top, w, h;
  int cnt = 0;
  while(scanf("#%*d @ %d,%d: %dx%d\n", &left, &top, &w, &h) == 4) {
    for(int i = left; i < left + w; i++) {
      for(int j = top; j < top + h; j++) {
        if(++fabric[i][j] == 2) {
          cnt++;
        }
      }
    }
  }
  printf("%d\n", cnt);
  return 0;
}
