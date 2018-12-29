#include <algorithm>
#include <cstdio>

#define SN 5177
#define SIZE 300
#define INF 0x3f3f3f3f

using namespace std;

int dp[SIZE + 1][SIZE + 1];

int fuel(int x, int y, int sn = SN) {
  int rackId = x + 10;
  return ((rackId * y + sn) * rackId) / 100 % 10 - 5;
}

int main() {
  for(int i = 0; i <= SIZE; i++) {
    dp[i][0] = dp[0][i] = 0;
  }
  for(int i = 1; i <= SIZE; i++) {
    for(int j = 1; j <= SIZE; j++) {
      dp[i][j] = fuel(j, i) + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
    }
  }
  int maxFuel = -INF, maxX = -1, maxY = -1, maxS = -1;
  for(int i = 3; i <= SIZE; i++) {
    for(int j = 3; j <= SIZE; j++) {
      int sqFuel = dp[i][j] - dp[i - 3][j] - dp[i][j - 3] + dp[i - 3][j - 3];
      if(sqFuel > maxFuel) {
        maxFuel = sqFuel; maxY = i - 2; maxX = j - 2;
      }
    }
  }
  printf("%d,%d\n", maxX, maxY);

  maxFuel = -INF;
  for(int i = 3; i <= SIZE; i++) {
    for(int j = 3; j <= SIZE; j++) {
      for(int s = 1; s < min(i, j); s++) {
        int sqFuel = dp[i][j] - dp[i - s][j] - dp[i][j - s] + dp[i - s][j - s];
        if(sqFuel > maxFuel) {
          maxFuel = sqFuel; maxY = i - s + 1; maxX = j - s + 1, maxS = s;
        }
      }
    }
  }
  printf("%d,%d,%d\n", maxX, maxY, maxS);
  return 0;
}
