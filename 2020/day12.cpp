#include <cstdio>
#include <vector>

using namespace std;

vector<pair<char, int>> plan;

void rotate(int steps, int& wx, int& wy) {
  if(steps % 2) { swap(wx, wy); wx = -wx; }
  if(steps / 2) { wx = -wx; wy = -wy; }
}

int run(int wx, int wy, bool ctrlWp) {
  int x = 0, y = 0;
  for(auto p : plan) {
    char ch; int n; tie(ch, n) = p;
    switch(ch) {
      case 'N': (ctrlWp ? wy : y) -= n; break;
      case 'S': (ctrlWp ? wy : y) += n; break;
      case 'E': (ctrlWp ? wx : x) += n; break;
      case 'W': (ctrlWp ? wx : x) -= n; break;
      case 'L': rotate(4 - n / 90, wx, wy); break;
      case 'R': rotate(n / 90, wx, wy); break;
      case 'F': x += n * wx; y += n * wy; break;
    }
  }
  return abs(x) + abs(y);
}

int main() {
  char ch; int n;
  while(scanf("%c%d\n", &ch, &n) > 0) {
    plan.emplace_back(ch, n);
  }
  printf("%d %d\n", run(1, 0, false), run(10, -1, true));
  return 0;
}
