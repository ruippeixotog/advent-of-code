#include <cstdio>
#include <vector>

#define TARGET 19690720

using namespace std;

vector<int> baseProg;

int runProg(vector<int> prog, int a, int b) {
  prog[1] = a; prog[2] = b;
  for(int pc = 0; pc < prog.size(); pc += 4) {
    switch(prog[pc]) {
      case 99:
        pc = prog.size();
        break;
      case 1:
        prog[prog[pc + 3]] = prog[prog[pc + 1]] + prog[prog[pc + 2]];
        break;
      case 2:
        prog[prog[pc + 3]] = prog[prog[pc + 1]] * prog[prog[pc + 2]];
        break;
    }
  }
  return prog[0];
}

int main() {
  int code;
  while(scanf("%d%*[,\n]", &code) > 0) {
    baseProg.push_back(code);
  }

  printf("%d\n", runProg(baseProg, 12, 2));

  for(int a = 0; a < 100; a++) {
    for (int b = 0; b < 100; b++) {
      if(runProg(baseProg, a, b) == TARGET) {
        printf("%d\n", 100 * a + b);
        return 0;
      }
    }
  }
  return 0;
}
