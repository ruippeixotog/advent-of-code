#include <cstdio>

#define MAXN 7

using namespace std;

int nPos[MAXN], initialPos[MAXN];

int main() {
  int n = 0;
  while(scanf("Disc #%*d has %d positions; at time=0, it is at position %d.\n",
              &nPos[n], &initialPos[n]) == 2) {
    n++;
  }

  int t; bool found = false;
  for(t = 0; !found; t++) {
    found = true;
    for(int i = 0; i < n; i++) {
      int pos = (initialPos[i] + t + i + 1) % nPos[i];
      if(pos != 0) { found = false; break; }
    }
  }
  printf("%d\n", t - 1);
  return 0;
}
