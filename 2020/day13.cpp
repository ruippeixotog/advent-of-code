#include <climits>
#include <cstdio>
#include <vector>

typedef long long ll;

using namespace std;

vector<int> schs;

int main() {
  int n; scanf("%d\n", &n);
  while(true) {
    int k; char ch;
    if(scanf("%[x],", &ch) > 0) schs.push_back(-1);
    else if(scanf("%d,", &k) > 0) schs.push_back(k);
    else break;
  }

  int minWait = INT_MAX, minBus = -1;
  for(int sch : schs) {
    if(sch != -1 && sch - n % sch < minWait) {
      minWait = sch - n % sch;
      minBus = sch;
    }
  }
  ll t = 0, cycle = 1;
  for(int i = 0; i < schs.size(); i++) {
    if(schs[i] == -1) continue;
    int reqMod = (schs[i] - i % schs[i]) % schs[i];
    while(t % schs[i] != reqMod) t += cycle;
    cycle *= schs[i];
  }
  printf("%d %lld\n", minWait * minBus, t);
  return 0;
}
