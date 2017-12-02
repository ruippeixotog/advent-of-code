#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#define INF 0x3f3f3f3f

using namespace std;

int main() {
  string line; int sum = 0;
  while(getline(cin, line)) {
    istringstream sin(line);
    int lo = INF, hi = -INF, cell;
    while(sin >> cell) {
      lo = min(lo, cell); hi = max(hi, cell);
    }
    sum += hi - lo;
  }
  printf("%d\n", sum);
  return 0;
}
