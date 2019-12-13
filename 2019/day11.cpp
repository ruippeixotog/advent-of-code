#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
#include "lib/intcode.cpp"

#define INF 0x3f3f3f3f

using namespace std;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

map<pair<int, int>, int> hull;

void paint(const Prog& prog) {
  int dir = 0, x = 0, y = 0;
  ProgState state(prog);
  while(state.exitReason != REASON_HALTED) {
    state.ins.push(hull[{y, x}]);
    runProgState(state);
    hull[{y, x}] = state.outs.front();
    state.outs.pop();
    dir = (dir + (state.outs.front() ? 1 : 3)) % 4;
    state.outs.pop();
    x += dx[dir]; y += dy[dir];
  }
}

void renderHull() {
  int minX = INF, minY = INF;
  for(auto entry : hull) {
    if(!entry.second) continue;
    minY = min(minY, entry.first.first);
    minX = min(minX, entry.first.second);
  }
  int curY = minY, curX = minX;
  for(auto entry : hull) {
    if(!entry.second) continue;
    while(curY < entry.first.first) {
      printf("\n");
      curY++; curX = minX;
    }
    while(curX < entry.first.second) {
      printf(" ");
      curX++;
    }
    printf("*");
    curX++;
  }
  printf("\n");
}

int main() {
  Prog baseProg;
  readProg(baseProg);

  paint(baseProg);
  printf("%d\n", (int) hull.size());

  hull.clear();
  hull[{0, 0}] = 1;
  paint(baseProg);
  renderHull();
  return 0;
}
