#include <cstdio>
#include "lib/intcode.cpp"

#define TARGET 19690720

using namespace std;

int runProgWithInputs(Prog& prog, int a, int b) {
  prog[1] = a; prog[2] = b;
  ProgState state(prog, {});
  runProgState(state);
  return state.prog[0];
}

int main() {
  Prog baseProg;
  readProg(baseProg);

  printf("%d\n", runProgWithInputs(baseProg, 12, 2));

  for(int a = 0; a < 100; a++) {
    for (int b = 0; b < 100; b++) {
      if(runProgWithInputs(baseProg, a, b) == TARGET) {
        printf("%d\n", 100 * a + b);
        return 0;
      }
    }
  }
  return 0;
}
