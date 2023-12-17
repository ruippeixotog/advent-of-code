#include <cstdio>
#include <iostream>

using namespace std;

int i = 2, j = 0;

char keypad[5][5] = {
  {  0,   0, '1',   0,   0},
  {  0, '2', '3', '4',   0},
  {'5', '6', '7', '8', '9'},
  {  0, 'A', 'B', 'C',   0},
  {  0,   0, 'D',   0,   0}
};

bool isValid(int i, int j) {
  return i >= 0 && i < 5 && j >= 0 && j < 5 && keypad[i][j];
}

int main() {
  string str;
  while(getline(cin, str)) {
    for(char ch: str) {
      int i1 = i, j1 = j;
      switch(ch) {
        case 'U': i1--; break;
        case 'D': i1++; break;
        case 'L': j1--; break;
        case 'R': j1++; break;
      }
      if(isValid(i1, j1)) { i = i1; j = j1; }
    }
    printf("%c", keypad[i][j]);
  }

  printf("\n");
  return 0;
}
