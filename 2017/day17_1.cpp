#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int step; scanf("%d\n", &step);

  vector<int> buf = { 0 };
  int pos = 0;
  for(int k = 1; k <= 2017; k++) {
    pos = (pos + step) % buf.size();
    buf.insert(next(buf.begin() + pos), k);
    pos++;
  }
  printf("%d\n", buf[(pos + 1) % buf.size()]);
  return 0;
}
