#include <algorithm>
#include <cstdio>
#include <queue>
#include "lib/intcode.cpp"

#define MAXN 200
#define ST (MAXN / 2)
#define INF 0x3f3f3f3f

using namespace std;

int di[] = { -1, 1, 0, 0 };
int dj[] = { 0, 0, -1, 1 };
char repr[] = {'#', '.', 'x'};

char grid[MAXN][MAXN];

int minI = ST, maxI = ST, minJ = ST, maxJ = ST;
int oxyI = -1, oxyJ = -1;

int explore(const ProgState& state, int i, int j, int step) {
  minI = min(minI, i); maxI = max(maxI, i);
  minJ = min(minJ, j); maxJ = max(maxJ, j);

  int best = INF;
  if(grid[i][j] == repr[2]) {
    best = step;
    oxyI = i, oxyJ = j;
  }
  for(int dir = 0; dir < 4; dir++) {
    if(!grid[i + di[dir]][j + dj[dir]]) {
      ProgState stateFork = state;
      stateFork.ins.push(dir + 1);
      runProgState(stateFork);

      int res = stateFork.outs.front();
      stateFork.outs.pop();

      grid[i + di[dir]][j + dj[dir]] = repr[res];
      if(res == 0) continue;
      best = min(best, explore(stateFork, i + di[dir], j + dj[dir], step + 1));
    }
  }
  return best;
}

int fillOxy() {
  queue<tuple<int, int, int>> q;
  q.emplace(0, oxyI, oxyJ);

  int longest = 0, steps, i, j;
  while(!q.empty()) {
    tie(steps, i, j) = q.front(); q.pop();
    if(grid[i][j] == repr[0] || grid[i][j] == 'O') continue;

    grid[i][j] = 'O';
    longest = max(longest, steps);

    for(int dir = 0; dir < 4; dir++) {
      q.emplace(steps + 1, i + di[dir], j + dj[dir]);
    }
  }
  return longest;
}

void render() {
  for(int i = minI - 1; i <= maxI + 1; i++) {
    for(int j = minJ - 1; j <= maxJ + 1; j++) {
      printf("%c", grid[i][j] ? grid[i][j] : ' ');
    }
    printf("\n");
  }
}

int main() {
  Prog baseProg;
  readProg(baseProg);
  grid[ST][ST] = 'D';

  int oxySteps = explore(baseProg, ST, ST, 0);
  render();
  int t = fillOxy();
  printf("%d %d\n", oxySteps, t);
  return 0;
}
