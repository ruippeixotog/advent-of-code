#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

map<string, vector<string>> adjs;

pair<int, int> countOrbit(const string& k) {
  int orbits = 0, sz = 1;
  for(string& adj : adjs[k]) {
    auto tmp = countOrbit(adj);
    orbits += tmp.first + tmp.second;
    sz += tmp.second;
  }
  return {orbits, sz};
}

pair<int, int> dist(const string& from, const string& to, const string& k) {
  int depthF = k == from ? 0 : INF, depthT = k == to ? 0 : INF;
  for(string& adj : adjs[k]) {
    auto tmp = dist(from, to, adj);
    if(tmp.first < INF && tmp.second < INF) {
      return tmp;
    }
    depthF = min(depthF, tmp.first + 1);
    depthT = min(depthT, tmp.second + 1);
  }
  return {depthF, depthT};
}

int main() {
  char from[10], to[10];
  while(scanf("%[^)])%s\n", from, to) > 0) {
    adjs[string(from)].emplace_back(to);
  }
  printf("%d\n", countOrbit("COM").first);
  auto res = dist("YOU", "SAN", "COM");
  printf("%d\n", res.first + res.second - 2);
  return 0;
}
