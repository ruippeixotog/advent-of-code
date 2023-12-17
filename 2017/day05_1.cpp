#include <cstdio>
#include <vector>

using namespace std;

int main() {
  vector<int> offsets; int k;
  while(scanf("%d\n", &k) > 0) {
    offsets.push_back(k);
  }

  int ptr = 0, steps = 0;
  for(; ptr >= 0 && ptr < offsets.size(); steps++) {
    ptr += offsets[ptr]++;
  }
  printf("%d\n", steps);
  return 0;
}
