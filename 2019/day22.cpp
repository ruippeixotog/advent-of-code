#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct ModCtx {
  ll mod;
  explicit ModCtx(ll mod): mod(mod) {}

  ll repeat(ll a, ll n, ll id, ll (ModCtx::* op)(ll, ll)) {
    if(n == 0) return id;
    ll halfRep = repeat(a, n / 2, id, op);
    return (this->*op)(halfRep, n % 2 ? (this->*op)(a, halfRep) : halfRep);
  }

  inline ll add(ll a, ll b) { return (a + b) % mod; }
  inline ll sub(ll a, ll b) { return (a + mod - b) % mod; }
  inline ll mul(ll a, ll b) { return repeat(a, b, 0, &ModCtx::add); }
  inline ll pow(ll a, ll p) { return repeat(a, p, 1, &ModCtx::mul); }

  // modular inverse exists only if mod is prime (or coprime to a)
  inline ll inv(ll a) { return pow(a, mod - 2); }
  inline ll div(ll a, ll b) { return mul(a, inv(b)); }
};

ll offset, jump;

void calcParams(const vector<string>& cmds, ll deckSize, ll reps) {
  ModCtx m(deckSize);
  offset = 0, jump = 1;
  int arg;
  for(const string& cmd : cmds) {
    if(sscanf(cmd.c_str(), "cut %d", &arg) == 1) {
      offset = m.sub(offset, arg);
    } else if(cmd == "deal into new stack") {
      offset = deckSize - offset - 1;
      jump = m.mul(jump, deckSize - 1);
    } else if(sscanf(cmd.c_str(), "deal with increment %d", &arg) == 1) {
      offset = m.mul(offset, arg);
      jump = m.mul(jump, arg);
    }
  }
  offset = m.div(
    m.mul(offset, m.sub(1, m.pow(jump, reps))),
    m.sub(1, jump)); // geometric series sum
  jump = m.pow(jump, reps);
}

ll findCardPos(ll card, ll deckSize) {
  ModCtx m(deckSize);
  return m.add(offset, m.mul(card, jump));
}

ll getCard(ll pos, ll deckSize) {
  ModCtx m(deckSize);
  return m.div(m.sub(pos, offset), jump);
}

int main() {
  vector<string> cmds; string cmd;
  while(getline(cin, cmd)) {
    cmds.push_back(cmd);
  }

  calcParams(cmds, 10007, 1);
  printf("%lld\n", findCardPos(2019, 10007));

  calcParams(cmds, 119315717514047LL, 101741582076661LL);
  printf("%lld\n", getCard(2020, 119315717514047LL));
  return 0;
}
