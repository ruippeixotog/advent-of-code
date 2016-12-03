#include <cstdio>
#include <iostream>

using namespace std;

int i = 1, j = 1;

bool isValid(int i, int j) {
  return i >= 0 && i < 3 && j >= 0 && j < 3;
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
    printf("%d", i * 3 + j + 1);
  }

  printf("\n");
  return 0;
}
