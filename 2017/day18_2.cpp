#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
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
  queue<ll> snd; int sndCnt = 0; ll* rcvWait = nullptr;

  Proc(Program& prog): program(prog) {}

  bool canRun() {
    return !rcvWait && stmtPtr >= 0 && stmtPtr < program.size();
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

function<void (Proc&)> compileSnd(string arg) {
  return [=](Proc& p) { p.snd.push(toValue(p, arg)); p.sndCnt++; };
}
function<void (Proc&)> compileSet(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) = toValue(p, arg2); };
}
function<void (Proc&)> compileAdd(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) += toValue(p, arg2); };
}
function<void (Proc&)> compileMul(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) *= toValue(p, arg2); };
}
function<void (Proc&)> compileMod(string arg1, string arg2) {
  return [=](Proc& p) { toRegPtr(p, arg1) %= toValue(p, arg2); };
}
function<void (Proc&)> compileRcv(string arg) {
  return [=](Proc& p) { p.rcvWait = &toRegPtr(p, arg); };
}
function<void (Proc&)> compileJgz(string arg1, string arg2) {
  return [=](Proc& p) { if(toValue(p, arg1) > 0) p.stmtPtr += toValue(p, arg2) - 1; };
}

map<string, function<function<void (Proc&)> (string)>> unOps = {
  { "snd", compileSnd }, { "rcv", compileRcv }
};

map<string, function<function<void (Proc&)> (string, string)>> binOps = {
  { "set", compileSet }, { "add", compileAdd }, { "mul", compileMul },
  { "mod", compileMod }, { "jgz", compileJgz }
};

Program readAndCompile() {
  Program program;
  string opCode, arg1, arg2;
  while(cin >> opCode) {
    if(unOps.count(opCode)) {
      cin >> arg1;
      program.push_back(unOps[opCode](arg1));
    } else {
      cin >> arg1 >> arg2;
      program.push_back(binOps[opCode](arg1, arg2));
    }
  }
  return program;
}

void coordRun(Program& program, Proc& p0, Proc& p1) {
  p0.regs['p'] = 0; p1.regs['p'] = 1;

  while(p0.canRun() || p1.canRun()) {
    p0.run();
    p1.run();
    if(!p0.snd.empty() && p1.rcvWait) {
      *p1.rcvWait = p0.snd.front();
      p1.rcvWait = nullptr; p0.snd.pop();
    }
    if(!p1.snd.empty() && p0.rcvWait) {
      *p0.rcvWait = p1.snd.front();
      p0.rcvWait = nullptr; p1.snd.pop();
    }
  }
}

int main() {
  Program program = readAndCompile();
  Proc p0(program), p1(program);
  coordRun(program, p0, p1);
  printf("%d\n", p1.sndCnt);
  return 0;
}
