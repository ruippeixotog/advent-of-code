#include <cstdio>
#include <iostream>
#include <string>

#define CMD_ON 1
#define CMD_OFF 2
#define CMD_TOGGLE 3

using namespace std;

bool readCmd(int* cmd, int* x0, int* y0, int* x1, int* y1) {
  string word;
  if(!(cin >> word)) return false;

  if(word == "turn") {
    cin >> word;
    *cmd = word == "on" ? CMD_ON : CMD_OFF;
  } else {
    *cmd = CMD_TOGGLE;
  }
  return scanf("%d,%d through %d,%d\n", x0, y0, x1, y1) > 0;
}

bool lights[1000][1000];

int main() {
  int cmd, x0, y0, x1, y1;

  while(readCmd(&cmd, &x0, &y0, &x1, &y1)) {
    for(int i = x0; i <= x1; i++) {
      for(int j = y0; j <= y1; j++) {
        switch(cmd) {
          case CMD_ON: lights[i][j] = true; break;
          case CMD_OFF: lights[i][j] = false; break;
          case CMD_TOGGLE: lights[i][j] = !lights[i][j]; break;
        }
      }
    }
  }
  int count = 0;
  for(int i = 0; i < 1000; i++) {
    for(int j = 0; j < 1000; j++) {
      if(lights[i][j]) count++;
    }
  }
  cout << count << endl;
  return 0;
}
