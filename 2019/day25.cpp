#include <iostream>
#include "lib/intcode.cpp"

using namespace std;

int main() {
  Prog baseProg;
  readProg(baseProg);

  ProgState state(baseProg);
  runInteractive(state, {
    {"Command?", []() {
      string line;
      getline(cin, line);
      return line;
    }}
  });
  return 0;
}
