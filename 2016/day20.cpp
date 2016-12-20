#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

#define MAXIP 4294967295

using namespace std;

typedef long long ll;

vector<pair<ll, ll>> rules;

int main() {
  ll a, b;
  while(scanf("%lld-%lld\n", &a, &b) == 2)
    rules.push_back({ a, b });

  sort(rules.begin(), rules.end());

  ll lowest = 0;
  for(int i = 0; i < rules.size() && rules[i].first == lowest; i++) {
    lowest = rules[i].second + 1;
    if(i < rules.size() - 1) lowest = min(lowest, rules[i + 1].first);
  }

  ll allowed = 0, last = 0;
  for(int i = 0; i < rules.size(); i++) {
    allowed += max(0LL, rules[i].first - last);
    last = max(last, rules[i].second + 1);
  }
  allowed += MAXIP - last + 1;

  printf("%lld\n", lowest);
  printf("%lld\n", allowed);
  return 0;
}
