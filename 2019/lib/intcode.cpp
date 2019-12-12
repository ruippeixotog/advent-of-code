#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>

#define REASON_HALTED 0
#define REASON_INPUT_WAIT 1

using namespace std;

typedef long long ll;

typedef vector<int> Prog;

struct ProgState {
  vector<int> prog;
  int pc;
  int rbase;
  queue<int> ins;
  queue<int> outs;
  int exitReason;

  ProgState(const Prog& prog): prog(prog), pc(0), rbase(0), exitReason(-1) {}
  ProgState(const Prog& prog, const vector<int>& input): ProgState(prog) {
    for(int in : input) {
      ins.push(in);
    }
  }
};

// (re)starts execution of a program in a given state
void runProgState(ProgState& state) {
  Prog& prog = state.prog;
  int& pc = state.pc;
  int& rbase = state.rbase;

  auto readP = [&prog, &rbase](int pc, int pos) {
    int param = prog[pc + pos];
    int flag = prog[pc] / (int) pow(10, pos + 1) % 10;
    switch(flag) {
      case 0: return prog[param];
      case 1: return param;
      case 2: return prog[rbase + param];
      default:
        fprintf(stderr, "Unknown read mode: %d\n", flag);
        return 0;
    }
  };

  auto writeP = [&prog, &rbase](int pc, int pos) {
    int param = prog[pc + pos];
    int flag = prog[pc] / (int) pow(10, pos + 1) % 10;
    switch(flag) {
      case 0: return &prog[param];
      case 2: return &prog[rbase + param];
      default:
        fprintf(stderr, "Unknown write mode: %d\n", flag);
        return (int*) nullptr;
    }
  };

  while(pc < prog.size()) {
    switch(prog[pc] % 100) {
      case 99:
        state.exitReason = REASON_HALTED;
        return;
      case 1:
        *writeP(pc, 3) = readP(pc, 1) + readP(pc, 2);
        pc += 4;
        break;
      case 2:
        *writeP(pc, 3) = readP(pc, 1) * readP(pc, 2);
        pc += 4;
        break;
      case 3:
        if(state.ins.empty()) {
          state.exitReason = REASON_INPUT_WAIT;
          return;
        }
        *writeP(pc, 1) = state.ins.front();
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
        *writeP(pc, 3) = readP(pc, 1) < readP(pc, 2);
        pc += 4;
        break;
      case 8:
        *writeP(pc, 3) = readP(pc, 1) == readP(pc, 2);
        pc += 4;
        break;
      case 9:
        state.rbase += readP(pc, 1);
        pc += 2;
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
int runProg(const Prog& prog, const vector<int>& input) {
  ProgState state(prog, input);
  runProgState(state);
  return state.outs.back();
}

void readProg(Prog& prog) {
  int code;
  while(scanf("%d%*[,\n]", &code) > 0) {
    prog.push_back(code);
  }
}
