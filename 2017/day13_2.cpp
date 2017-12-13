#include <cstdio>
#include <map>

using namespace std;

map<int, int> ranges;

bool valid(int delay) {
  for(auto e : ranges) {
    if((e.first + delay) % ((e.second - 1) * 2) == 0)
      return false;
  }
  return true;
}

int main() {
  int layer, range;
  while(scanf("%d: %d\n", &layer, &range) == 2) {
    ranges[layer] = range;
  }
  for(layer = 0; !valid(layer); layer++);
  printf("%d\n", layer);
  return 0;
}
