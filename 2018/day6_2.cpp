#include <algorithm>
#include <cstdio>
#include <vector>

#define MAXN 2000

using namespace std;

vector<int> xs, ys;

int main() {
  int x, y;
  while(scanf("%d, %d\n", &x, &y) == 2) {
    xs.push_back(x + 500);
    ys.push_back(y + 500);
  }

  int cnt = 0;
  for(int x0 = 0; x0 < MAXN; x0++) {
    for(int y0 = 0; y0 < MAXN; y0++) {
      int totalDist = 0;
      for(int i = 0; i < xs.size(); i++) {
        totalDist += abs(x0 - xs[i]) + abs(y0 - ys[i]);
      }
      if(totalDist < 10000) {
        cnt++;
      }
    }
  }

  printf("%d\n", cnt);
  return 0;
}
