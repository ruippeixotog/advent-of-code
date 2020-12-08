#include <cstdio>
#include <set>
#include <string>
#include <vector>

using namespace std;
  
pair<bool, int> runProg(const vector<pair<string, int>>& prog) {
  set<int> prevExecuted;

  int pc = 0, acc = 0;
  while(pc >= 0 && pc < prog.size() && !prevExecuted.count(pc)) {
    auto inst = prog[pc];
    prevExecuted.insert(pc);

    if(inst.first == "acc") acc += inst.second;
    else if(inst.first == "jmp") pc += inst.second - 1;
    pc++;
  }
  return {pc == prog.size(), acc};
}

pair<bool, int> fixProg(vector<pair<string, int>>& prog) {
  for(auto& inst : prog) {
    if(inst.first != "acc") {
      inst.first = inst.first == "nop" ? "jmp" : "nop";
      auto res = runProg(prog);
      if(res.first) return {true, res.second};
      inst.first = inst.first == "nop" ? "jmp" : "nop";
    }
  }
  return {false, 0};
}

int main() {
  vector<pair<string, int>> prog;
  char op[5]; int arg;
  while(scanf("%s %d", op, &arg) > 0) {
    prog.emplace_back(op, arg);
  }
  int res1 = runProg(prog).second;
  int res2 = fixProg(prog).second;
  printf("%d %d\n", res1, res2);
  return 0;
}
