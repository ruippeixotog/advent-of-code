#include <cmath>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdio>

#define REASON_HALTED 0
#define REASON_INPUT_WAIT 1

using namespace std;

typedef long long ll;

typedef unordered_map<int, ll> Prog;

struct ProgState {
  Prog prog;
  int pc;
  int rbase;
  queue<ll> ins;
  queue<ll> outs;
  int exitReason;

  ProgState(const Prog& prog): prog(prog), pc(0), rbase(0), exitReason(-1) {}
  ProgState(const Prog& prog, const vector<ll>& input): ProgState(prog) {
    for(ll in : input) {
      ins.push(in);
    }
  }
};

// Starts or restarts execution of a program in a given state.
void runProgState(ProgState& state) {
  Prog& prog = state.prog;
  int& pc = state.pc;
  int& rbase = state.rbase;

  auto readP = [&prog, &rbase](int pc, int pos) {
    ll param = prog[pc + pos];
    ll flag = prog[pc] / (ll) pow(10, pos + 1) % 10;
    switch(flag) {
      case 0: return prog[param];
      case 1: return param;
      case 2: return prog[rbase + param];
      default:
        fprintf(stderr, "Unknown read mode: %lld\n", flag);
        return 0LL;
    }
  };

  auto writeP = [&prog, &rbase](int pc, int pos) {
    ll param = prog[pc + pos];
    ll flag = prog[pc] / (int) pow(10, pos + 1) % 10;
    switch(flag) {
      case 0: return &prog[param];
      case 2: return &prog[rbase + param];
      default:
        fprintf(stderr, "Unknown write mode: %lld\n", flag);
        return (ll*) nullptr;
    }
  };

  while(true) {
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
        pc = readP(pc, 1) ? (int) readP(pc, 2) : pc + 3;
        break;
      case 6:
        pc = readP(pc, 1) ? pc + 3 : (int) readP(pc, 2);
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
        fprintf(stderr, "Illegal instruction: %lld\n", prog[pc] % 100);
        return;
    }
  }
}

// Runs a program with the given inputs and return the last output value.
ll runProg(const Prog& prog, const vector<ll>& input) {
  ProgState state(prog, input);
  runProgState(state);
  return state.outs.back();
}

// Reads a program from stdin.
void readProg(Prog& prog) {
  ll code; int idx = 0;
  while(scanf("%lld%*[,\n]", &code) > 0) {
    prog[idx++] = code;
  }
}

// Reads an ASCII line from a program's outputs.
string readLine(ProgState& state) {
  string str;
  while(!state.outs.empty()) {
    char ch = state.outs.front(); state.outs.pop();
    if(ch == '\n') break;
    else str.push_back(ch);
  }
  return str;
}

// Writes an ASCII line to a program's inputs, ending with a newline.
void writeLine(ProgState& state, const string& cmd) {
  for(char ch : cmd + "\n") state.ins.push(ch);
}

// Reads an ASCII 2D grid from a program's inputs.
// The grid ends with an empty line.
void readGrid(ProgState& state, vector<string>& grid) {
  while(!state.outs.empty()) {
    string line = readLine(state);
    if(line.empty() && grid.back().empty()) break;
    grid.emplace_back(line);
  }
}

// Runs an interactive program that accepts ASCII inputs (from prompts) and
// writes ASCII output or large numbers. Answers can be automated using the
// provided answer map.
void runInteractive(ProgState& state, unordered_map<string, function <string()>> answers) {
  while(state.exitReason != REASON_HALTED) {
    runProgState(state);

    while(!state.outs.empty()) {
      if(state.outs.front() >= 256) {
        printf("%lld\n", state.outs.front());
        state.outs.pop();
      }
      string line = readLine(state);
      if(answers.count(line)) {
        printf("%s ", line.c_str());
        string reply = answers[line]();
        writeLine(state, reply);
        printf("%s\n", reply.c_str());
      } else {
        printf("%s\n", line.c_str());
      }
    }
  }
}
