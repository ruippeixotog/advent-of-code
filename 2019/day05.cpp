#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> baseProg;

int runProg(vector<int> prog, int input) {
  auto readP = [&prog](int pc, int pos) {
    int param = prog[pc + pos];
    int flag = prog[pc] / (int) pow(10, pos + 1) % 10;
    return flag == 0 ? prog[param] : param;
  };

  vector<int> outs;
  for(int pc = 0; pc < prog.size(); ) {
    switch(prog[pc] % 100) {
      case 99:
        pc = prog.size();
        break;
      case 1:
        prog[prog[pc + 3]] = readP(pc, 1) + readP(pc, 2);
        pc += 4;
        break;
      case 2:
        prog[prog[pc + 3]] = readP(pc, 1) * readP(pc, 2);
        pc += 4;
        break;
      case 3:
        prog[prog[pc + 1]] = input;
        pc += 2;
        break;
      case 4:
        outs.push_back(readP(pc, 1));
        pc += 2;
        break;
      case 5:
        pc = readP(pc, 1) ? readP(pc, 2) : pc + 3;
        break;
      case 6:
        pc = readP(pc, 1) ? pc + 3 : readP(pc, 2);
        break;
      case 7:
        prog[prog[pc + 3]] = readP(pc, 1) < readP(pc, 2);
        pc += 4;
        break;
      case 8:
        prog[prog[pc + 3]] = readP(pc, 1) == readP(pc, 2);
        pc += 4;
        break;
      default:
        fprintf(stderr, "Illegal instruction: %d\n", prog[pc] % 100);
        return -1;
    }
  }
  return *outs.rbegin();
}

int main() {
  int code;
  while(scanf("%d%*[,\n]", &code) > 0) {
    baseProg.push_back(code);
  }

  printf("%d\n", runProg(baseProg, 1));
  printf("%d\n", runProg(baseProg, 5));
  return 0;
}
