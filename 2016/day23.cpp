#include <cstdio>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define CPY_VV 0
#define CPY_VR 1
#define CPY_RV 2
#define CPY_RR 3
#define INC 4
#define DEC 5
#define JNZ_VV 6
#define JNZ_VR 7
#define JNZ_RV 8
#define JNZ_RR 9
#define TGL 10

using namespace std;

vector<tuple<int, int, int>> program;

int regs[] = {12, 0, 0, 0};

void toggle(int tgt) {
  int opcode = get<0>(program[tgt]);
  switch(opcode) {
    case CPY_VV: opcode = JNZ_VV; break;
    case CPY_VR: opcode = JNZ_VR; break;
    case CPY_RV: opcode = JNZ_RV; break;
    case CPY_RR: opcode = JNZ_RR; break;
    case INC: opcode = DEC; break;
    case DEC: opcode = INC; break;
    case JNZ_VV: opcode = CPY_VV; break;
    case JNZ_VR: opcode = CPY_VR; break;
    case JNZ_RV: opcode = CPY_RV; break;
    case JNZ_RR: opcode = CPY_RR; break;
    case TGL: opcode = INC; break;
  }
  get<0>(program[tgt]) = opcode;
}

int main() {
  string str;
  while(getline(cin, str)) {
    char reg1, reg2; int v, v2;
    if(sscanf(str.c_str(), "cpy %d %c", &v, &reg1) == 2) {
      program.push_back(make_tuple(CPY_VR, v, reg1 - 'a'));
    }
    else if(sscanf(str.c_str(), "cpy %c %c", &reg1, &reg2) == 2) {
      program.push_back(make_tuple(CPY_RR, reg1 - 'a', reg2 - 'a'));
    }
    else if(sscanf(str.c_str(), "inc %c", &reg1) == 1) {
      program.push_back(make_tuple(INC, reg1 - 'a', 0));
    }
    else if(sscanf(str.c_str(), "dec %c", &reg1) == 1) {
      program.push_back(make_tuple(DEC, reg1 - 'a', 0));
    }
    else if(sscanf(str.c_str(), "jnz %d %d", &v, &v2) == 2) {
      program.push_back(make_tuple(JNZ_VV, v, v2));
    }
    else if(sscanf(str.c_str(), "jnz %d %c", &v, &reg1) == 2) {
      program.push_back(make_tuple(JNZ_VR, v, reg1 - 'a'));
    }
    else if(sscanf(str.c_str(), "jnz %c %d", &reg1, &v) == 2) {
      program.push_back(make_tuple(JNZ_RV, reg1 - 'a', v));
    }
    else if(sscanf(str.c_str(), "jnz %c %c", &reg1, &reg2) == 2) {
      program.push_back(make_tuple(JNZ_RR, reg1 - 'a', reg2 - 'a'));
    }
    else if(sscanf(str.c_str(), "tgl %c", &reg1) == 1) {
      program.push_back(make_tuple(TGL, reg1 - 'a', 0));
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
      case CPY_VR: regs[arg2] = arg1; break;
      case CPY_RR: regs[arg2] = regs[arg1]; break;
      case INC: regs[arg1]++; break;
      case DEC: regs[arg1]--; break;
      case JNZ_VV: if(arg1) pc += arg2 - 1; break;
      case JNZ_VR: if(arg1) pc += regs[arg2] - 1; break;
      case JNZ_RV: if(regs[arg1]) pc += arg2 - 1; break;
      case JNZ_RR: if(regs[arg1]) pc += regs[arg2] - 1; break;
      case TGL:
        int tgt = pc + regs[arg1];
        if(tgt >= 0 && tgt < program.size()) toggle(tgt);
        break;
    }
    pc++;
  }

  printf("%d\n", regs[0]);
  return 0;
}
