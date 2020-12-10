#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long ll;

using namespace std;

int main() {
  vector<int> ks = {0};
  int k;
  while(scanf("%d", &k) > 0) {
    ks.push_back(k);
  }
  sort(ks.begin(), ks.end());

  int diffs[3] = {0, 0, 1};
  for(int i = 1; i < ks.size(); i++) {
    diffs[ks[i] - ks[i - 1] - 1]++;
  }

  vector<ll> dp(ks.size());
  dp[0] = 1;
  for(int i = 1; i < ks.size(); i++) {
    for(int j = i - 1; j >= 0 && ks[i] - ks[j] <= 3; j--) {
      dp[i] += dp[j];
    }
  }
  printf("%d %lld\n", diffs[0] * diffs[2], dp[ks.size() - 1]);
  return 0;
}
