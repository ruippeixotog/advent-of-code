#include <cstdio>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define CPY_VAL 0
#define CPY_REG 1
#define INC 2
#define DEC 3
#define JNZ 4

using namespace std;

vector<tuple<int, int, int>> program;

int regs[] = {0, 0, 1, 0};

int main() {
  string str;
  while(getline(cin, str)) {
    char reg1, reg2; int v;
    if(sscanf(str.c_str(), "cpy %d %c", &v, &reg1) == 2) {
      program.push_back(make_tuple(CPY_VAL, v, reg1 - 'a'));
    }
    else if(sscanf(str.c_str(), "cpy %c %c", &reg1, &reg2) == 2) {
      program.push_back(make_tuple(CPY_REG, reg1 - 'a', reg2 - 'a'));
    }
    else if(sscanf(str.c_str(), "inc %c", &reg1) == 1) {
      program.push_back(make_tuple(INC, reg1 - 'a', 0));
    }
    else if(sscanf(str.c_str(), "dec %c", &reg1) == 1) {
      program.push_back(make_tuple(DEC, reg1 - 'a', 0));
    }
    else if(sscanf(str.c_str(), "jnz %c %d", &reg1, &v) == 2) {
      program.push_back(make_tuple(JNZ, reg1 - 'a', v));
    }
    else {
      fprintf(stderr, "ERROR: unrecognized instruction '%s'\n", str.c_str());
    }
  }

  int pc = 0;
  while(pc < program.size()) {
    int opcode, arg1, arg2;
    tie(opcode, arg1, arg2) = program[pc];

    switch(opcode) {
      case CPY_VAL: regs[arg2] = arg1; break;
      case CPY_REG: regs[arg2] = regs[arg1]; break;
      case INC: regs[arg1]++; break;
      case DEC: regs[arg1]--; break;
      case JNZ: if(regs[arg1]) pc += arg2 - 1; break;
    }
    pc++;
  }

  printf("%d\n", regs[0]);
  return 0;
}
