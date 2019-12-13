#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pos;
typedef long double ld;

ld vecAngle(const Pos& p1, const Pos& p2) {
  return atan2(p2.second - p1.second, p2.first - p1.first);
}

int vecSize2(const Pos& p1, const Pos& p2) {
  return (p2.second - p1.second) * (p2.second - p1.second) +
    (p2.first - p1.first) * (p2.first - p1.first);
}

int main() {
  vector<Pos> asteroids;
  string row;
  for(int i = 0; getline(cin, row); i++) {
    for (int j = 0; j < row.size(); j++) {
      if(row[j] == '#') {
        asteroids.emplace_back(j, i);
      }
    }
  }

  int best = 0;
  Pos bestPos = {-1, -1};
  for(auto a1 : asteroids) {
    set<ld> angles;
    for(auto a2 : asteroids) {
      if(a1 == a2) continue;
      angles.insert(vecAngle(a1, a2));
    }
    if(best < angles.size()) {
      best = angles.size();
      bestPos = a1;
    }
  }
  printf("%d\n", best);

  vector<tuple<ld, int, Pos>> angles;
  for(auto a1 : asteroids) {
    if(a1 == bestPos) continue;
    ld upAngle = fmod(vecAngle(bestPos, a1) + 2.5 * M_PI, 2 * M_PI);
    angles.emplace_back(upAngle, vecSize2(bestPos, a1), a1);
  }
  sort(angles.begin(), angles.end());

  set<Pos> destroyed;
  ld lastAngle = -1.0;
  int idx = 0;
  while(true) {
    if(get<0>(angles[idx]) != lastAngle) {
      destroyed.insert(get<2>(angles[idx]));
      lastAngle = get<0>(angles[idx]);
    }
    if(destroyed.size() == 200) break;
    idx = (idx + 1) % (int) angles.size();
  }
  printf("%d\n", get<2>(angles[idx]).first * 100 + get<2>(angles[idx]).second);
  return 0;
}
