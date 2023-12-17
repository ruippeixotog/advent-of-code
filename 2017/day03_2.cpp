#include <algorithm>
#include <cstdio>

using namespace std;

int grid[1000][1000];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int n; scanf("%d\n", &n);

  int x = 500, y = 500, dir = 0;
  grid[x][y] = 1;
  while(grid[x][y] <= n) {
    x += dx[dir]; y += dy[dir];
    for(int i = -1; i <= 1; i++) {
      for(int j = -1; j <= 1; j++) {
        if(i || j) grid[x][y] += grid[x + i][y + j];
      }
    }
    int ccwDir = (dir + 1) % 4;
    if(!grid[x + dx[ccwDir]][y + dy[ccwDir]]) {
      dir = ccwDir;
    }
  }
  printf("%d\n", grid[x][y]);
  return 0;
}
