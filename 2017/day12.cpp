#include <cstdio>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<int, vector<int>> adjs;

set<int> visited;

int ffill(int k, int parent = -1) {
  if(visited.count(k)) return 0;
  visited.insert(k);

  int cnt = 1;
  for(int adj : adjs[k]) {
    if(adj != parent) cnt += ffill(adj, k);
  }
  return cnt;
}

int main() {
  int id, adj;
  while(scanf("%d <-> %d", &id, &adj) == 2) {
    adjs[id].push_back(adj);
    while(scanf(", %d", &adj) == 1) {
      adjs[id].push_back(adj);
    }
  }
  int mainGroup = ffill(0), groupsCnt = 1;
  for(auto e : adjs) {
    if(ffill(e.first) > 0) groupsCnt++;
  }
  printf("%d %d\n", mainGroup, groupsCnt);
  return 0;
}
