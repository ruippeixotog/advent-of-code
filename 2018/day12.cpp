#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

#define RLEN 5

using namespace std;

typedef long long ll;

string state;
set<string> rules;

ll offset;
map<string, pair<ll, ll>> mem;

void evolve(ll currGen, ll toGen) {
  for(ll it = currGen; it < toGen; it++) {
    if(mem.count(state)) {
      ll period = it - mem[state].first;
      ll cycles = (toGen - it) / period;
      if(cycles > 0) {
        it += cycles * period - 1;
        offset += cycles * (offset - mem[state].second);
        continue;
      }
    }

    string refState = string(RLEN - 1, '.') + state + string(RLEN - 1, '.');
    string newState(state.length() + (RLEN - 1) * 2, '.');

    for(int i = RLEN / 2; i < refState.length() - RLEN / 2; i++) {
      string patt = refState.substr(i - RLEN / 2, RLEN);
      if(rules.count(patt)) {
        newState[i] = '#';
      }
    }
    int from = newState.find('#');
    newState = newState.substr(from, newState.rfind('#') - from + 1);

    mem[state] = {it, offset};
    state = newState;
    offset += from - RLEN + 1;
  }
}

ll getSum() {
  ll sum = 0;
  for(int i = 0; i < state.length(); i++) {
    if(state[i] == '#') sum += i + offset;
  }
  return sum;
}

int main() {
  scanf("initial state: ");
  getline(cin, state);

  char rule[RLEN + 1], result;
  while(scanf("%s => %c\n", rule, &result) == 2) {
    if(result == '#') rules.emplace(rule);
  }

  evolve(0, 20);
  printf("%lld\n", getSum());
  evolve(20, 50000000000);
  printf("%lld\n", getSum());
  return 0;
}
