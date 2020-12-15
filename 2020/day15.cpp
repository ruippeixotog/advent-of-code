#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> initial = {9, 3, 1, 0, 8, 4};

int main() {
  unordered_map<int, vector<int>> lastK;

  int last = -1, res1 = -1;
  for(int i = 0; i < 30000000; i++) {
    if(i == 2020) res1 = last;

    int next = i < initial.size() ? initial[i] :
      lastK[last].size() < 2 ? 0 :
      *lastK[last].rbegin() - *(lastK[last].rbegin() + 1);

    lastK[next].push_back(i);
    last = next;
  }
  printf("%d %d\n", res1, last);
  return 0;
}
