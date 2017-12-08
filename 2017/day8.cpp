#include <algorithm>
#include <cstdio>
#include <map>
#include <string>

using namespace std;

map<string, function<void (int&, int)>> ops = {
  { "inc", [] (int& a, int b) { a += b; } },
  { "dec", [] (int& a, int b) { a -= b; } }
};

map<string, function<bool (int, int)>> condOps = {
  { "<", [] (int a, int b) { return a < b; } },
  { "<=", [] (int a, int b) { return a <= b; } },
  { ">", [] (int a, int b) { return a > b; } },
  { ">=", [] (int a, int b) { return a >= b; } },
  { "==", [] (int a, int b) { return a == b; } },
  { "!=", [] (int a, int b) { return a != b; } }
};

char reg[6], op[4], condReg[6], condOp[4];
int arg, condArg;

map<string, int> regs;

int main() {
  int maxRegEver = 0;
  while(scanf("%s %s %d if %s %s %d", reg, op, &arg, condReg, condOp, &condArg) > 0) {
    if(condOps[string(condOp)](regs[string(condReg)], condArg)) {
      ops[string(op)](regs[string(reg)], arg);
      maxRegEver = max(maxRegEver, regs[string(reg)]);
    }
  }
  int maxReg = 0;
  for(auto e : regs) maxReg = max(maxReg, e.second);
  printf("%d %d\n", maxReg, maxRegEver);
  return 0;
}
