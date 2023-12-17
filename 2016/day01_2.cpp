#include <cstdio>
#include <cstdlib>

using namespace std;

int x = 500, y = 500, d = 0;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool visited[1000][1000];

bool move(char dir, int n) {
  d = (d + (dir == 'R' ? 1 : 3)) % 4;
  while(n--) {
    x += dx[d];
    y += dy[d];
    if(visited[x][y]) return true;
    visited[x][y] = true;
  }
  return false;
}

int main() {
  char dir; int n;
  scanf("%c%d", &dir, &n);
  if(!move(dir, n)) {
    while(scanf(", %c%d", &dir, &n) > 0 && !move(dir, n));
  }
  printf("%d\n", abs(x - 500) + abs(y - 500));
  return 0;
}
