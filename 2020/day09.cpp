#include <algorithm>
#include <cstdio>
#include <vector>

#define PRE 25

typedef long long ll;

using namespace std;

int main() {
  vector<ll> ks;
  ll k;
  while(scanf("%lld", &k) > 0) {
    ks.push_back(k);
  }

  ll res1 = 0;
  for(int i = PRE; i < ks.size() && !res1; i++) {
    bool found = false;
    for(int j = i - PRE; j < i && !found; j++) {
      for(int k = j + 1; k < i; k++) {
        if(ks[j] + ks[k] == ks[i]) {
          found = true;
          break;
        }
      }
    }
    if(!found) res1 = ks[i];
  }

  ll res2 = 0;
  for(int i = 0; i < ks.size() && !res2; i++) {
    ll sum = ks[i], low = ks[i], high = ks[i];
    for(int j = i + 1; j < ks.size() && !res2; j++) {
      sum += ks[j];
      low = min(low, ks[j]);
      high = max(high, ks[j]);
      if(sum == res1) res2 = low + high;
    }
  }
  printf("%lld %lld\n", res1, res2);
  return 0;
}
