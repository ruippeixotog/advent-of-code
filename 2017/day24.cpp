#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<int, vector<int>> adjs;

map<int, set<int>> used;
int maxStrength, longest, longestStrength;

void dfs(int k, int strength, int depth) {
  maxStrength = max(maxStrength, strength);
  if(depth >= longest) {
    if(depth == longest) longestStrength = max(longestStrength, strength);
    else { longest = depth; longestStrength = strength; }
  }
  for(int adj : adjs[k]) {
    int mn = min(k, adj), mx = max(k, adj);
    if(!used[mn].count(mx)) {
      used[mn].insert(mx);
      dfs(adj, strength + k + adj, depth + 1);
      used[mn].erase(mx);
    }
  }
}

int main() {
  int p1, p2;
  while(scanf("%d/%d\n", &p1, &p2) == 2) {
    adjs[p1].push_back(p2);
    adjs[p2].push_back(p1);
  }
  dfs(0, 0, 0);
  printf("%d %d\n", maxStrength, longestStrength);
  return 0;
}
