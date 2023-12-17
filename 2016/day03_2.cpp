#include <algorithm>
#include <cstdio>

using namespace std;

bool valid(int a1, int a2, int a3) {
  int maxA = max(a1, max(a2, a3));
  return a1 + a2 + a3 - maxA > maxA;
}

int main() {
  int a1, a2, a3, a4, a5, a6, a7, a8, a9;
  int cnt = 0;
  while(
    scanf("%d %d %d\n", &a1, &a2, &a3) > 0 &&
    scanf("%d %d %d\n", &a4, &a5, &a6) > 0 &&
    scanf("%d %d %d\n", &a7, &a8, &a9) > 0) {

    cnt += valid(a1, a4, a7) +
           valid(a2, a5, a8) +
           valid(a3, a6, a9);
  }
  printf("%d\n", cnt);
  return 0;
}
