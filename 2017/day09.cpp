#include <cstdio>

#define MODE_NORMAL 0
#define MODE_GARBAGE 1
#define MODE_ESCAPE 2

using namespace std;

struct State {
  int level = 0, mode = MODE_NORMAL;
  int lsum = 0, gcount = 0;
};

void handleNormal(char ch, State& s) {
  switch(ch) {
    case '{': s.level++; s.lsum += s.level; break;
    case '}': s.level--; break;
    case '<': s.mode = MODE_GARBAGE; break;
  }
}

void handleGarbage(char ch, State& s) {
  switch(ch) {
    case '>': s.mode = MODE_NORMAL; break;
    case '!': s.mode = MODE_ESCAPE; break;
    default: s.gcount++;
  }
}

void handleEscape(char ch, State& s) {
  s.mode = MODE_GARBAGE;
}

int main() {
  char ch; State s;
  while(scanf("%c", &ch) > 0) {
    switch(s.mode) {
      case MODE_NORMAL: handleNormal(ch, s); break;
      case MODE_GARBAGE: handleGarbage(ch, s); break;
      case MODE_ESCAPE: handleEscape(ch, s); break;
    }
  }
  printf("%d %d\n", s.lsum, s.gcount);
  return 0;
}
