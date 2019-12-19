#include <cstdio>
#include "lib/intcode.cpp"

#define MAXN 10000
#define SQ 100

using namespace std;

Prog baseProg;

bool fits(int x, int y) {
  return runProg(baseProg, {x, y}) &&
    runProg(baseProg, {x + SQ - 1, y}) &&
    runProg(baseProg, {x, y + SQ - 1}) &&
    runProg(baseProg, {x + SQ - 1, y + SQ - 1});
}

int linsearch(int x) {
  for(int y = 0; y < MAXN; y++) {
    if(fits(x, y)) return y;
  }
  return -1;
}

pair<int, int> binsearch() {
  int minX = 0, maxX = MAXN;
  while(minX < maxX) {
    int midX = (minX + maxX) / 2;

    if(linsearch(midX) == -1) minX = midX + 1;
    else maxX = midX;
  }
  return {minX, linsearch(minX)};
}

int main() {
  readProg(baseProg);

  int cnt = 0;
  for(int y = 0; y < 50; y++) {
    for(int x = 0; x < 50; x++) {
      cnt += runProg(baseProg, {x, y});
    }
  }
  auto pos = binsearch();

  printf("%d\n", cnt);
  printf("%d\n", pos.first * MAXN + pos.second);
  return 0;
}
