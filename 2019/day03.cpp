#include <cstdio>
#include <map>
#include <set>

#define INF 0x3f3f3f3f

using namespace std;

map<char, int> dx = {{ 'L', -1 }, { 'R', 1 }, { 'U', 0 }, { 'D', 0 }};
map<char, int> dy = {{ 'L', 0 }, { 'R', 0 }, { 'U', -1 }, { 'D', 1 }};

map<pair<int, int>, set<int>> seen;
map<tuple<int, int, int>, int> delay;

int main() {
  int wireId = 0, currX = 0, currY = 0, steps = 0;

  char dir;
  int cnt;
  while(scanf("%c%d", &dir, &cnt) == 2) {
    while(cnt--) {
      currX += dx[dir];
      currY += dy[dir];
      steps++;
      seen[{currX, currY}].insert(wireId);
      if(!delay.count({currX, currY, wireId})) {
        delay[{currX, currY, wireId}] = steps;
      }
    }
    scanf("%c", &dir);
    if(dir == '\n') {
      wireId++;
      currX = currY = steps = 0;
    }
  }

  int closest = INF, fastest = INF;
  for(const auto& entry : seen) {
    if(entry.second.size() > 1) {
      closest = min(closest, abs(entry.first.first) + abs(entry.first.second));

      int durationSum = 0;
      for(int wireId : entry.second) {
        durationSum += delay[{entry.first.first, entry.first.second, wireId}];
      }
      fastest = min(fastest, durationSum);
    }
  }
  printf("%d %d\n", closest, fastest);
  return 0;
}
