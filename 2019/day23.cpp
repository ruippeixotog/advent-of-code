#include <set>
#include <vector>
#include "lib/intcode.cpp"

using namespace std;

void runNetwork(const Prog& prog, int n) {
  vector<ProgState> states(n, prog);
  for(int i = 0; i < n; i++) {
    states[i].ins.push(i);
  }

  ll natX = 0, natY = 0;
  vector<bool> idle(n, false);
  set<ll> deliveredYs;

  for(int i = 0; true; i = (i + 1) % n) {
    if(i == 0 && find(idle.begin(), idle.end(), false) == idle.end()) {
      if(deliveredYs.empty()) {
        printf("%lld\n", natY);
      }
      states[0].ins.push(natX);
      states[0].ins.push(natY);

      if(deliveredYs.count(natY)) {
        printf("%lld\n", natY);
        return;
      }
      deliveredYs.insert(natY);
    }

    idle[i] = false;
    if(states[i].exitReason == REASON_INPUT_WAIT && states[i].ins.empty()) {
      states[i].ins.push(-1);
      idle[i] = true;
    }
    runProgState(states[i]);

    auto& outs = states[i].outs;
    idle[i] = idle[i] && outs.empty();

    while(!outs.empty()) {
      int addr = outs.front(); outs.pop();
      ll x = outs.front(); outs.pop();
      ll y = outs.front(); outs.pop();

      if(addr == 255) {
        natX = x; natY = y;
      } else {
        states[addr].ins.push(x);
        states[addr].ins.push(y);
      }
    }
  }
}

int main() {
  Prog baseProg;
  readProg(baseProg);

  ProgState state(baseProg);
  runNetwork(baseProg, 50);
  return 0;
}
