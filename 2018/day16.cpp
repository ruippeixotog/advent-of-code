#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <string>

#define OPS 16

using namespace std;

int reg[4], bf[4], aft[4];

map<string, function<void (int, int, int)>> ops = {
  {"addr", [](int a, int b, int c) { return reg[c] = reg[a] + reg[b]; }},
  {"addi", [](int a, int b, int c) { return reg[c] = reg[a] + b; }},
  {"mulr", [](int a, int b, int c) { return reg[c] = reg[a] * reg[b]; }},
  {"muli", [](int a, int b, int c) { return reg[c] = reg[a] * b; }},
  {"banr", [](int a, int b, int c) { return reg[c] = reg[a] & reg[b]; }},
  {"bani", [](int a, int b, int c) { return reg[c] = reg[a] & b; }},
  {"borr", [](int a, int b, int c) { return reg[c] = reg[a] | reg[b]; }},
  {"bori", [](int a, int b, int c) { return reg[c] = reg[a] | b; }},
  {"setr", [](int a, int b, int c) { return reg[c] = reg[a]; }},
  {"seti", [](int a, int b, int c) { return reg[c] = a; }},
  {"gtir", [](int a, int b, int c) { return reg[c] = a > reg[b]; }},
  {"gtri", [](int a, int b, int c) { return reg[c] = reg[a] > b; }},
  {"gtrr", [](int a, int b, int c) { return reg[c] = reg[a] > reg[b]; }},
  {"eqir", [](int a, int b, int c) { return reg[c] = a == reg[b]; }},
  {"eqri", [](int a, int b, int c) { return reg[c] = reg[a] == b; }},
  {"eqrr", [](int a, int b, int c) { return reg[c] = reg[a] == reg[b]; }},
};

set<string> opcodes[OPS];

void markInvalid(int opcode, const string& op) {
  if(opcodes[opcode].erase(op) && opcodes[opcode].size() == 1) {
    string finalOp = *opcodes[opcode].begin();
    for(int i = 0; i < OPS; i++) {
      if(i != opcode) markInvalid(i, finalOp);
    }
  }
}

int main() {
  for(auto & validSet : opcodes) {
    for(const auto& e : ops) {
      validSet.insert(e.first);
    }
  }

  int cnt = 0;
  int opcode, argA, argB, argC;
  while(scanf("Before: [%d, %d, %d, %d]\n", bf, bf + 1, bf + 2, bf + 3) == 4) {
    scanf("%d %d %d %d\n", &opcode, &argA, &argB, &argC);
    scanf("After: [%d, %d, %d, %d]\n", aft, aft + 1, aft + 2, aft + 3);

    int opCnt = 0;
    for(const auto& e : ops) {
      memcpy(reg, bf, sizeof(reg));
      e.second(argA, argB, argC);
      if(memcmp(reg, aft, sizeof(reg)) == 0) {
        opCnt++;
      } else {
        markInvalid(opcode, e.first);
      }
    }
    cnt += opCnt >= 3;
  }
  printf("%d\n", cnt);

  memset(reg, 0, sizeof(reg));
  while(scanf("%d %d %d %d\n", &opcode, &argA, &argB, &argC) == 4) {
    ops[*opcodes[opcode].begin()](argA, argB, argC);
  }
  printf("%d\n", reg[0]);
  return 0;
}
