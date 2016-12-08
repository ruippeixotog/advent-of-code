#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#define ROWS 6
#define COLS 50

using namespace std;

bool screen[ROWS][COLS];

void printScreen() {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      fprintf(stderr, screen[i][j] ? "#" : ".");
    }
    fprintf(stderr, "\n");
  }
}

int main() {
  string str;
  while(getline(cin, str)) {
    int row, col, shift;

    if(sscanf(str.c_str(), "rect %dx%d", &col, &row) > 0) {
      for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
          screen[i][j] = true;
        }
      }
    }
    else if(sscanf(str.c_str(), "rotate row y=%d by %d", &row, &shift) > 0) {
      bool tmp[COLS];
      memcpy(tmp, screen[row], COLS - shift);
      memcpy(screen[row], screen[row] + COLS - shift, shift);
      memcpy(screen[row] + shift, tmp, COLS - shift);
    }
    else if(sscanf(str.c_str(), "rotate column x=%d by %d", &col, &shift) > 0) {
      bool tmp[ROWS];
      for(int i = 0; i < ROWS - shift; i++) tmp[i] = screen[i][col];
      for(int i = 0; i < shift; i++) screen[i][col] = screen[ROWS - shift + i][col];
      for(int i = 0; i < ROWS - shift; i++) screen[i + shift][col] = tmp[i];
    }
    else {
      fprintf(stderr, "ERROR: unrecognized instruction '%s'\n", str.c_str());
    }
  }

  int cnt = 0;
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(screen[i][j]) cnt++;
    }
  }
  printScreen();
  printf("%d\n", cnt);
  return 0;
}
