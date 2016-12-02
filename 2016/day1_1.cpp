#include <cstdio>
#include <cstdlib>

using namespace std;

int x, y, d;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void move(char dir, int n) {
  d = (d + (dir == 'R' ? 1 : 3)) % 4;
  x += n * dx[d];
  y += n * dy[d];
}

int main() {
  char dir; int n;
  scanf("%c%d", &dir, &n);
  move(dir, n);

  while(scanf(", %c%d", &dir, &n) > 0)
    move(dir, n);

  printf("%d\n", abs(x) + abs(y));
  return 0;
}
