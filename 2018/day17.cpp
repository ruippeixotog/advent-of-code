#include <algorithm>
#include <cstdio>

#define MAXN 2000
#define DOWN 0
#define LEFT 1
#define RIGHT 2

using namespace std;

char grid[MAXN][MAXN];
int minY, maxY;

void fixNonRest(int i, int j, int dir) {
  while(grid[i][j] == '~') {
    grid[i][j] = '|';
    j += dir == LEFT ? -1 : 1;
  }
}

bool flow(int i, int j, int dir) {
  if(i > maxY || grid[i][j] == '|') return true;
  if(grid[i][j]) return false;

  grid[i][j] = '|';
  if(flow(i + 1, j, DOWN)) return true;

  bool res;
  if(dir == DOWN) {
    bool resLeft = flow(i, j - 1, LEFT);
    bool resRight = flow(i, j + 1, RIGHT);
    if(!resLeft && resRight) fixNonRest(i, j - 1, LEFT);
    if(resLeft && !resRight) fixNonRest(i, j + 1, RIGHT);
    res = resLeft || resRight;
  } else {
    res = flow(i, j + (dir == LEFT ? -1 : 1), dir);
  }
  if(!res) grid[i][j] = '~';
  return res;
}

int main() {
  char ch; int x, y0, y1;
  minY = MAXN, maxY = 0;
  while(scanf("%[xy]=%d, %*c=%d..%d\n", &ch, &x, &y0, &y1) > 0) {
    if(ch == 'x') {
      minY = min(minY, y0);
      maxY = max(maxY, y1);
      for(int j = y0; j <= y1; j++) {
        grid[j][x] = '#';
      }
    } else {
      minY = min(minY, x);
      maxY = max(maxY, x);
      for(int i = y0; i <= y1; i++) {
        grid[x][i] = '#';
      }
    }
  }
  flow(minY, 500, DOWN);

  int cnt1 = 0, cnt2 = 0;
  for(int i = 0; i < MAXN; i++) {
    for(int j = 0; j < MAXN; j++) {
      if(grid[i][j] == '~' || grid[i][j] == '|') {
        cnt1++;
      }
      if(grid[i][j] == '~') {
        cnt2++;
      }
    }
  }
  printf("%d %d\n", cnt1, cnt2);
  return 0;
}
