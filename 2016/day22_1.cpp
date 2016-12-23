#include <cstdio>
#include <iostream>

#define MAXX 32
#define MAXY 30

using namespace std;

int used[MAXX][MAXY];
int avail[MAXX][MAXY];

int main() {
  string str;
  while(getline(cin, str)) {
    int x, y, us, av;
    if(sscanf(str.c_str(), "/dev/grid/node-x%d-y%d %*dT %dT %dT", &x, &y, &us, &av) == 4) {
      used[x][y] = us;
      avail[x][y] = av;
    }
  }

  int cnt = 0;
  for(int x1 = 0; x1 < MAXX; x1++) {
    for(int y1 = 0; y1 < MAXY; y1++) {
      for(int x2 = 0; x2 < MAXX; x2++) {
        for(int y2 = 0; y2 < MAXY; y2++) {
          if((x1 != x2 || y1 != y2) && used[x1][y1] && used[x1][y1] < avail[x2][y2])
            cnt++;
        }
      }
    }
  }
  printf("%d\n", cnt);
  return 0;
}
