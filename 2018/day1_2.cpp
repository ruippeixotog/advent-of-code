#include <cstdio>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  vector<int> freqs;
  char sign; int val;
  while(scanf("%c%d\n", &sign, &val) == 2) {
    freqs.push_back((sign == '+' ? 1 : -1) * val);
  }

  int sum = 0, idx = 0;
  unordered_set<int> visited;
  while(!visited.count(sum)) {
    visited.insert(sum);
    sum += freqs[(idx++) % freqs.size()];
  }
  printf("%d\n", sum);
  return 0;
}
