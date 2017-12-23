#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int sgn(int val) { return (0 < val) - (val < 0); }

int main() {
  vector<vector<int>> pas;

  int px, py, pz, vx, vy, vz, ax, ay, az;
  while(scanf("p=<%d,%d,%d>, v=<%d,%d,%d>, a=<%d,%d,%d>\n",
              &px, &py, &pz, &vx, &vy, &vz, &ax, &ay, &az) == 9) {

    pas.push_back({abs(ax) + abs(ay) + abs(az),
                   vx * sgn(ax) + vy * sgn(ay) + vz * sgn(az),
                   px * sgn(ax) + py * sgn(ay) + pz * sgn(az) });
  }
  auto it = min_element(pas.begin(), pas.end());
  printf("%d\n", (int) (it - pas.begin()));
  return 0;
}
