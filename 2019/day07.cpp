#include <algorithm>
#include <cstdio>
#include <vector>
#include "lib/intcode.cpp"

using namespace std;

int runProgChain(const vector<int>& prog, int n, const vector<vector<int>>& initialInputs) {
  vector<ProgState> states(n, prog);
  for(int i = 0; i < n; i++) {
    for(int in : initialInputs[i]) {
      states[i].ins.push(in);
    }
  }
  for(int i = 0; states[i].exitReason != REASON_HALTED; i = (i + 1) % n) {
    int prevElem = (i + n - 1) % n;
    while(!states[prevElem].outs.empty()) {
      states[i].ins.push(states[prevElem].outs.front());
      states[prevElem].outs.pop();
    }
    runProgState(states[i]);
  }
  return states[n - 1].outs.front();
}

int main() {
  vector<int> baseProg;
  readProg(baseProg);

  vector<vector<int>> baseInputs[] = {
    {{0}, {1}, {2}, {3}, {4}},
    {{5}, {6}, {7}, {8}, {9}}
  };
  for(auto& baseInput : baseInputs) {
    int bestSingle = 0;
    do {
      vector<vector<int>> inputs = baseInput;
      inputs[0].push_back(0);
      bestSingle = max(bestSingle, runProgChain(baseProg, 5, inputs));
    } while(next_permutation(baseInput.begin(), baseInput.end()));

    printf("%d\n", bestSingle);
  }
  return 0;
}
