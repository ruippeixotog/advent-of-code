#include "lib/intcode.cpp"

using namespace std;

int main() {
  Prog baseProg;
  readProg(baseProg);

  ProgState state(baseProg);
  // !(A & B & C) & D
  writeLine(state, "NOT J J");
  writeLine(state, "AND A J");
  writeLine(state, "AND B J");
  writeLine(state, "AND C J");
  writeLine(state, "NOT J J");
  writeLine(state, "AND D J");
  writeLine(state, "WALK");
  runInteractive(state, {});

  ProgState state2(baseProg);
  // !(A & B & C) & D & (E | H)
  writeLine(state2, "NOT J J");
  writeLine(state2, "AND A J");
  writeLine(state2, "AND B J");
  writeLine(state2, "AND C J");
  writeLine(state2, "NOT J J");
  writeLine(state2, "AND D J");
  writeLine(state2, "OR E T");
  writeLine(state2, "OR H T");
  writeLine(state2, "AND T J");
  writeLine(state2, "RUN");
  runInteractive(state2, {});

  return 0;
}
