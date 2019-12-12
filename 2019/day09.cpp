#include "lib/intcode.cpp"

using namespace std;

int main() {
  Prog baseProg;
  readProg(baseProg);

  printf("%lld\n", runProg(baseProg, {1}));
  printf("%lld\n", runProg(baseProg, {2}));
  return 0;
}
