#include <algorithm>
#include <cstdio>
#include <map>
#include <string>

using namespace std;

map<string, int> dx = {
  { "n", 0 }, { "ne", 1 }, { "se", 1 },
  { "s", 0 }, { "sw", -1 }, { "nw", -1 }
};

map<string, int> dy = {
  { "n", -2 }, { "ne", -1 }, { "se", 1 },
  { "s", 2 }, { "sw", 1 }, { "nw", -1 }
};

int dist(int x, int y) {
  return (abs(y) - abs(x)) / 2 + abs(x);
}

int main() {
  int x = 0, y = 0, maxDist = 0;
  char cdir[3];
  while(scanf("%[nsew],", cdir) > 0) {
    x += dx[string(cdir)];
    y += dy[string(cdir)];
    maxDist = max(maxDist, dist(x, y));
  }
  printf("%d %d\n", dist(x, y), maxDist);
  return 0;
}
