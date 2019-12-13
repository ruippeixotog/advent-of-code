#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <unistd.h>
#include "lib/intcode.cpp"

#define MAXX 60
#define MAXY 25

using namespace std;

int sig(int k) { return k == 0 ? 0 : k / abs(k); }

template<typename T> T poll(queue<T>& queue) {
  T v = queue.front(); queue.pop(); return v;
}

int repr[] = {' ', '#', 'x', '_', 'o'};

struct GameState {
  int grid[MAXY][MAXX], blockCount;
  int ballX, paddleX;
  int score;

  GameState(): blockCount(0), ballX(-1), score(0) {
    memset(grid, 0, sizeof(grid));
  };

  void update(queue<ll>& outs) {
    while(!outs.empty()) {
      int x = poll(outs), y = poll(outs), tid = poll(outs);
      if (x == -1 && y == 0) {
        score = tid;
        continue;
      }
      switch (tid) {
        case 2: blockCount++; break;
        case 3: paddleX = x; break;
        case 4: ballX = x; break;
      }
      grid[y][x] = tid;
    }
  }

  void render() {
    for(int i = 0; i < MAXY; i++) {
      for(int j = 0; j < MAXX; j++) {
        printf("%c", repr[grid[i][j]]);
      }
      printf("\n");
    }
    printf("Score: %d\n", score);
  }

  void renderLive() {
    usleep(20000);
    printf("\033[2J\033[1;1H");
    render();
  }
};

int main(int argc, char* argv[]) {
  Prog baseProg;
  readProg(baseProg);

  GameState gameState;
  ProgState state(baseProg);
  state.prog[0] = 2;
  int initialBlocks = -1;
  while(state.exitReason != REASON_HALTED) {
    runProgState(state);
    gameState.update(state.outs);
    if(initialBlocks < 0) {
      initialBlocks = gameState.blockCount;
    }
    state.ins.push(sig(gameState.ballX - gameState.paddleX));
  }
  printf("%d\n", gameState.blockCount);
  printf("%d\n", gameState.score);
  return 0;
}
