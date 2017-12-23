#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct Proc;
typedef vector<function<void (Proc&)>> Program;

struct Proc {
  Program& program;
  map<char, ll> regs;
  int stmtPtr = 0;
  int mulCnt = 0;

  Proc(Program& prog): program(prog) {}

  bool canRun() {
    return stmtPtr >= 0 && stmtPtr < program.size();
  }

  void run() {
    while(canRun()) {
      program[stmtPtr](*this);
      stmtPtr++;
    }
  }
};

ll toValue(Proc& p, const string& arg) {
  if(arg[0] >= 'a' && arg[0] <= 'z') return p.regs[arg[0]];
  return stoll(arg);
}

ll& toRegPtr(Proc& p, const string& arg) {
  return p.regs[arg[0]];
}

function<void (Proc&)> compileSet(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) = toValue(p, arg2); };
}
function<void (Proc&)> compileSub(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) -= toValue(p, arg2); };
}
function<void (Proc&)> compileMul(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) *= toValue(p, arg2); p.mulCnt++; };
}
function<void (Proc&)> compileJnz(string arg1, string arg2) {
  return [=](Proc& p) { if(toValue(p, arg1) != 0) p.stmtPtr += toValue(p, arg2) - 1; };
}

map<string, function<function<void (Proc&)> (string, string)>> binOps = {
  { "set", compileSet }, { "sub", compileSub },
  { "mul", compileMul }, { "jnz", compileJnz }
};

Program readAndCompile() {
  Program program;
  string opCode, arg1, arg2;
  while(cin >> opCode) {
    cin >> arg1 >> arg2;
    program.push_back(binOps[opCode](arg1, arg2));
  }
  return program;
}

int main() {
  Program program = readAndCompile();
  Proc p(program);
  p.run();
  for(auto e : p.regs) { cerr << e.first << " " << e.second << endl; }
  cerr << "h " << p.regs['h'] << endl;

  printf("%d\n", p.mulCnt);
  return 0;
}
