#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>

#define REASON_HALTED 0
#define REASON_INPUT_WAIT 1

using namespace std;

struct ProgState {
  vector<int> prog;
  int pc;
  queue<int> ins;
  queue<int> outs;
  int exitReason;

  ProgState(const vector<int>& prog): prog(prog), pc(0), exitReason(-1) {}
  ProgState(const vector<int>& prog, const vector<int>& input): ProgState(prog) {
    for(int in : input) {
      ins.push(in);
    }
  }
};

// (re)starts execution of a program in a given state
void runProgState(ProgState& state) {
  vector<int>& prog = state.prog;
  int& pc = state.pc;

  auto readP = [&prog](int pc, int pos) {
    int param = prog[pc + pos];
    int flag = prog[pc] / (int) pow(10, pos + 1) % 10;
    return flag == 0 ? prog[param] : param;
  };

  while(pc < prog.size()) {
    switch(prog[pc] % 100) {
      case 99:
        state.exitReason = REASON_HALTED;
        return;
      case 1:
        prog[prog[pc + 3]] = readP(pc, 1) + readP(pc, 2);
        pc += 4;
        break;
      case 2:
        prog[prog[pc + 3]] = readP(pc, 1) * readP(pc, 2);
        pc += 4;
        break;
      case 3:
        if(state.ins.empty()) {
          state.exitReason = REASON_INPUT_WAIT;
          return;
        }
        prog[prog[pc + 1]] = state.ins.front();
        state.ins.pop();
        pc += 2;
        break;
      case 4:
        state.outs.push(readP(pc, 1));
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
        return;
    }
  }
  fprintf(stderr, "Program counter outside bounds\n");
  state.exitReason = REASON_HALTED;
}

// Run a program with the given inputs and return the last output value
int runProg(const vector<int>& prog, const vector<int>& input) {
  ProgState state(prog, input);
  runProgState(state);
  return state.outs.back();
}

void readProg(vector<int>& prog) {
  int code;
  while(scanf("%d%*[,\n]", &code) > 0) {
    prog.push_back(code);
  }
}
