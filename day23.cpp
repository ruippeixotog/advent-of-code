#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<function<void ()>> program;
int insPtr;
int a = 0, b = 0;

int* readReg() {
  char regName[2]; scanf(" %[ab]", regName);
  return regName[0] == 'a' ? &a : &b;
}

int readOffset() {
  int offset; cin >> offset;
  return offset;
}

pair<int*, int> readRegOffset() {
  char regName[2]; int offset;
  scanf(" %[ab], %d", regName, &offset);
  return make_pair(regName[0] == 'a' ? &a : &b, offset);
}

void read() {
  string ins;
  while(cin >> ins) {
    if(ins == "hlf") {
      int* reg = readReg();
      program.push_back([=] () { *reg /= 2; });
    }
    else if(ins == "tpl") {
      int* reg = readReg();
      program.push_back([=] () { *reg *= 3; });
    }
    else if(ins == "inc") {
      int* reg = readReg();
      program.push_back([=] () { (*reg)++; });
    }
    else if(ins == "jmp") {
      int offset = readOffset();
      program.push_back([=] () { insPtr += offset - 1; });
    }
    else if(ins == "jie") {
      pair<int*, int> args = readRegOffset();
      program.push_back([=] () {
        if(*args.first % 2 == 0) insPtr += args.second - 1;
      });
    }
    else if(ins == "jio") {
      pair<int*, int> args = readRegOffset();
      program.push_back([=] () {
        if(*args.first == 1) insPtr += args.second - 1;
      });
    }
  }
}

void run() {
  while(insPtr < program.size()) {
    program[insPtr]();
    insPtr++;
  }
}

int main() {
  read();
  run();
  cout << b << endl;
  return 0;
}
