#include <cstdio>
#include <vector>
#include "lib/intcode.cpp"

using namespace std;

int main() {
  vector<int> baseProg;
  readProg(baseProg);

  printf("%d\n", runProg(baseProg, {1}));
  printf("%d\n", runProg(baseProg, {5}));
  return 0;
}
