#include <cstdio>

#define A 182

int a = A, b = 0, c = 0, d = 0;

int it = 100; // limit the number of loops for easy diffing

void full() {
  d = a; // 1
  c = 14; // 2
  do {
    b = 182; // 3
    do {
      d++; // 4
      b--; // 5
    } while(b); // 6

    c--; // 7
  } while(c); // 8

  while(it--) {
    a = d; // 9
    do {
      // 10
      b = a; // 11
      a = 0; // 12
      while(true) {
        c = 2; // 13
        do {
          if(!b) { // 14
            goto break2; // 15
          }
          b--; // 16
          c--; // 17
        } while(c); // 18
        a++; // 19
      } // 20

      break2:
      b = 2; // 21
      while(true) {
        if(!c) { // 22
          break; // 23
        }
        b--; // 24
        c--; // 25
      } // 26

      // 27
      printf("%d\n", b); // 28
    } while(a); // 29
  } // 30
}

void optimized() {
  d = 14 * 182 + a; // 1-8

  while(it--) {
    a = d; // 9
    do {
      c = a % 2 ? 1 : 2, b = 0, a = a / 2; // 10-20
      b = 2 - c; // 21-26
      printf("%d\n", b); // 27-28
    } while(a); // 29
  } // 30
}

void optimized2() {
  d = 14 * 182 + a;
  while(it--) {
    for(a = d; a > 0; a /= 2) {
      printf("%d\n", a % 2);
    }
  }
}

void solver() {
  int baseD = 14 * 182;
  int currD = 0;
  while(currD <= baseD) {
    currD = currD * 2 + 1;
    currD = currD * 2;
  }
  printf("%d\n", currD - baseD);
}

int main() {
  solver();
  return 0;
}
