#include <cstdio>
#include <set>

#define MAXN 20000

using namespace std;

typedef long long ll;

char content[MAXN];

int main() {
  scanf("%s", content);

  ll len = 0;
  int mult = 1, width, reps;
  multiset<pair<int, int>> finishPos;

  for(int i = 0; content[i]; i++) {
    while(!finishPos.empty() && finishPos.begin()->first <= i) {
      mult /= finishPos.begin()->second;
      finishPos.erase(finishPos.begin());
    }

    if(sscanf(content + i, "(%dx%d)", &width, &reps) == 2) {
      while(content[i] != ')') i++;
      mult *= reps;
      finishPos.insert({ i + width + 1, reps });
    } else {
      len += mult;
    }
  }
  printf("%lld\n", len);
  return 0;
}
