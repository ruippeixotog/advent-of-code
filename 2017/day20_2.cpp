#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;
typedef tuple<ll, ll, ll> Point;

Point operator+(Point p1, Point p2) {
  return { get<0>(p1) + get<0>(p2),
           get<1>(p1) + get<1>(p2),
           get<2>(p1) + get<2>(p2) };
}

Point operator*(Point p1, int t) {
  return { get<0>(p1) * t, get<1>(p1) * t, get<2>(p1) * t };
}

Point operator/(Point p1, int t) {
  return { get<0>(p1) / t, get<1>(p1) / t, get<2>(p1) / t };
}

int main() {
  vector<tuple<Point, Point, Point>> ptDefs;

  int px, py, pz, vx, vy, vz, ax, ay, az;
  while(scanf("p=<%d,%d,%d>, v=<%d,%d,%d>, a=<%d,%d,%d>\n",
              &px, &py, &pz, &vx, &vy, &vz, &ax, &ay, &az) == 9) {

    ptDefs.emplace_back(make_tuple(px, py, pz),
                        make_tuple(vx, vy, vz),
                        make_tuple(ax, ay, az));
  }

  vector<bool> destroyed(ptDefs.size()); Point p, v, a;
  for(int t = 0; t < 1000; t++) {
    map<Point, int> points;
    for(int i = 0; i < ptDefs.size(); i++) {
      if(destroyed[i]) continue;

      tie(p, v, a) = ptDefs[i];
      Point atT = p + v * t + a * t * (t + 1) / 2;

      auto res = points.insert({ atT, i });
      if(!res.second) {
        destroyed[i] = destroyed[res.first->second] = true;
      }
    }
  }

  int cnt = 0;
  for(int i = 0; i < ptDefs.size(); i++) {
    if(!destroyed[i]) cnt++;
  }
  printf("%d\n", cnt);
  return 0;
}
