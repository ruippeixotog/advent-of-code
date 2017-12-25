#include <cstdio>
#include <cstring>
#include <map>

#define MAXT 200000

using namespace std;

struct Action {
  bool write; bool toRight; char newState;
};

struct State {
  Action actions[2];
};

struct Turing {
  bool tape[MAXT];
  int cursor = MAXT / 2;
  map<char, State> states;
  char currState;

  void doAction(Action& action) {
    tape[cursor] = action.write;
    cursor += (action.toRight ? 1 : -1);
    currState = action.newState;
  }

  void run(int steps) {
    while(steps--) {
      doAction(states[currState].actions[tape[cursor]]);
    }
  }
};

Turing t;

int main() {
  int steps;
  scanf("Begin in state %c.\n", &t.currState);
  scanf("Perform a diagnostic checksum after %d steps.\n", &steps);

  char st; int act; char direction[7];
  while(scanf("I"), scanf("n state %c:\n", &st) == 1) {
    while(scanf("If the current value is %d:\n", &act) == 1) {
      scanf("- Write the value %d.\n", (int*) &t.states[st].actions[act].write);
      scanf("- Move one slot to the %s\n", direction);
      scanf("- Continue with state %c.\n", &t.states[st].actions[act].newState);
      t.states[st].actions[act].toRight = !strcmp(direction, "right.");
    }
  }
  t.run(steps);

  int sum = 0;
  for (bool v: t.tape) sum += v;
  printf("%d\n", sum);
  return 0;
}
