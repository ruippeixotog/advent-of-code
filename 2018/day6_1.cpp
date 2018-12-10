#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#define MAXN 1000

using namespace std;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int grid[MAXN][MAXN];
int dist[MAXN][MAXN];

vector<int> xs, ys;

int ffill(int id, int x, int y) {
  if(x < 0 || x >= MAXN || y < 0 || y >= MAXN) {
    return -1;
  }
  if(grid[x][y] != id) {
    return 0;
  }
  grid[x][y] = -1;
  int cnt = 1;
  for(int dir = 0; dir < 4; dir++) {
    int subCnt = ffill(id, x + dx[dir], y + dy[dir]);
    if(subCnt < 0) return -1;
    cnt += subCnt;
  }
  return cnt;
}

int main() {
  int x, y;
  while(scanf("%d, %d\n", &x, &y) == 2) {
    xs.push_back(x);
    ys.push_back(y);
  }

  memset(dist, 0x3f, sizeof(dist));

  for(int i = 0; i < xs.size(); i++) {
    for(int x0 = 0; x0 < MAXN; x0++) {
      for(int y0 = 0; y0 < MAXN; y0++) {
        int d = abs(x0 - xs[i]) + abs(y0 - ys[i]);

        if(d == dist[x0][y0]) {
          grid[x0][y0] = -1;
        }
        if(d < dist[x0][y0]) {
          grid[x0][y0] = i;
          dist[x0][y0] = d;
        }
      }
    }
  }

  int best = 0;
  for(int i = 0; i < xs.size(); i++) {
    int subCnt = ffill(i, xs[i], ys[i]);
    if(subCnt >= 0) {
      best = max(best, subCnt);
    }
  }

  printf("%d\n", best);
  return 0;
}
