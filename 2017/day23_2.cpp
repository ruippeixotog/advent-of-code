#include <cstdio>

using namespace std;

int a = 1, b, c, d, e, f, g, h;

int main() {
  b = 79; // 1: set b 79
  c = b; // 2: set c b
  if(a) { // 3-4: jnz a 2, jnz 1 5
    b = b * 100 + 100000; // 5-6: mul b 100, sub b -100000
    c = b + 17000; // 7-8: set c b, sub c -17000
  }
  for(; b <= c; b += 17) {
    //  f = 1; // 9: set f 1
    //  for(d = 2; d < b; d++) { // 10: set d 2
    //    for(e = 2; e < b; e++) { // 11: set e 2
    //      if (d * e == b) { // 12-15: set g d, mul g e, sub g b, jnz g 2
    //        f = 0; // 16: set f 0
    //      }
    //    } // 17-20: sub e -1, set g e, sub g b, jnz g -8
    //  } // 21-24: sub d -1, set g d, sub g b, jnz g -13
    //  if (!f) { // 25: jnz f 2
    //    h++; // 26: sub h -1
    //  }
    for(d = 2; d < b; d++) {
      if(b % d == 0) { h++; break; }
    }
  } // 27-32: set g b, sub g c, jnz g 2, jnz 1 3, sub b -17, jnz 1 -23

  printf("%d\n", h);
  return 0;
}
