#include <cstdio>
#include <iostream>
#include <map>

#define NBITS 36

typedef long long ll;

using namespace std;

inline ll bset(ll mask, int b) { return mask | (1LL << b); }
inline ll bunset(ll mask, int b) { return mask & ~(1LL << b); }

void memWrite1(map<ll, ll>& mem, char* mask, ll addr, ll val) {
  for(int i = 0; i < NBITS; i++) {
    if(mask[NBITS - i - 1] == '0') val = bunset(val, i);
    if(mask[NBITS - i - 1] == '1') val = bset(val, i);
  }
  mem[addr] = val;
}

void memWrite2(map<ll, ll>& mem, char* mask, ll addr, ll val, int idx) {
  if(idx == NBITS) { mem[addr] = val; return; }
  
  switch(mask[NBITS - idx - 1]) {
    case '0':
      memWrite2(mem, mask, addr, val, idx + 1); break;
    case '1':
      memWrite2(mem, mask, bset(addr, idx), val, idx + 1); break;
    default:
      memWrite2(mem, mask, bset(addr, idx), val, idx + 1);
      memWrite2(mem, mask, bunset(addr, idx), val, idx + 1);
  }
}

ll getSum(map<ll, ll>& mem) {
  ll sum = 0;
  for(auto e : mem) { sum += e.second; }
  return sum;
}

int main() {
  map<ll, ll> mem1, mem2;
  char mask[NBITS + 1];

  string line;
  while(getline(cin, line)) {
    ll addr, val;
    sscanf(line.c_str(), "mask = %s", mask);
    if(sscanf(line.c_str(), "mem[%lld] = %lld\n", &addr, &val) > 0) {
      memWrite1(mem1, mask, addr, val);
      memWrite2(mem2, mask, addr, val, 0);
    }
  }
  printf("%lld %lld\n", getSum(mem1), getSum(mem2));
  return 0;
}
