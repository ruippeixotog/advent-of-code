#include <algorithm>
#include <cstdio>

using namespace std;

bool grid[1000][1000];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int n; scanf("%d\n", &n);

  int x = 500, y = 500, k = 1, dir = 0;
  grid[x][y] = true;
  while(k < n) {
    x += dx[dir]; y += dy[dir];
    grid[x][y] = true;
    k++;

    int ccwDir = (dir + 1) % 4;
    if(!grid[x + dx[ccwDir]][y + dy[ccwDir]]) {
      dir = ccwDir;
    }
  }
  printf("%d\n", abs(x - 500) + abs(y - 500));
  return 0;
}
