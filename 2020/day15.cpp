#include <cstdio>
#include <vector>

#define TGT 30000000

using namespace std;

vector<int> initial = {9, 3, 1, 0, 8, 4};

int prevIdx[TGT], diff[TGT];

int main() {
  int last = -1, res1 = -1;
  for(int i = 0; i < TGT; i++) {
    if(i == 2020) res1 = last;

    int next = i < initial.size() ? initial[i] : diff[last];
    diff[next] = prevIdx[next] ? i + 1 - prevIdx[next] : 0;
    prevIdx[next] = i + 1;
    last = next;
  }
  printf("%d %d\n", res1, last);
  return 0;
}
