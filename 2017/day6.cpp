#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

#define BLOCKS 16

using namespace std;

int main() {
  vector<int> mem(BLOCKS);
  for(int i = 0; i < BLOCKS; i++) {
    scanf("%d", &mem[i]);
  }

  map<vector<int>, int> seen;
  int redists = 0;
  for(; !seen.count(mem); redists++) {
    seen[mem] = redists;

    int idx = max_element(mem.begin(), mem.end()) - mem.begin();
    int val = mem[idx];

    mem[idx] = 0;
    while(val > 0) {
      idx = (idx + 1) % BLOCKS;
      mem[idx]++; val--;
    }
  }
  printf("%d %d\n", redists, redists - seen[mem]);
  return 0;
}
