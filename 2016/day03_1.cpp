#include <algorithm>
#include <cstdio>

using namespace std;

bool valid(int a1, int a2, int a3) {
  int maxA = max(a1, max(a2, a3));
  return a1 + a2 + a3 - maxA > maxA;
}

int main() {
  int a1, a2, a3;
  int cnt = 0;
  while(scanf("%d %d %d\n", &a1, &a2, &a3) > 0) {
    if(valid(a1, a2, a3)) cnt++;
  }
  printf("%d\n", cnt);
  return 0;
}
