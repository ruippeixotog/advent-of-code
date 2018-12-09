#include <cstdio>
#include <unordered_set>

#define MAXN 1000

using namespace std;

int fabric[MAXN][MAXN];

int main() {
  int id, left, top, w, h;
  unordered_set<int> valid;
  while(scanf("#%d @ %d,%d: %dx%d\n", &id, &left, &top, &w, &h) == 5) {
    bool addToValid = true;
    for(int i = left; i < left + w; i++) {
      for(int j = top; j < top + h; j++) {
        if(fabric[i][j]) {
          valid.erase(fabric[i][j]);
          addToValid = false;
          fabric[i][j] = -1;
        } else {
          fabric[i][j] = id;
        }
      }
    }
    if(addToValid) {
      valid.insert(id);
    }
  }
  printf("%d\n", *valid.begin());
  return 0;
}
