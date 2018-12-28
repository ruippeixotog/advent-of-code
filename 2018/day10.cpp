#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#define MAXY 15 // tweaked value
#define INF 0x3f3f3f3f

using namespace std;

struct Point {
  int x, y, dx, dy;

  void move() {
    x += dx; y += dy;
  }
};

int main() {
  vector<Point> points;
  Point p;
  while(scanf("position=<%d, %d> velocity=<%d, %d>\n", &p.x, &p.y, &p.dx, &p.dy) == 4) {
    points.push_back(p);
  }

  for(int it = 1; it < 200000; it++) {
    int minX = INF, maxX = -INF, minY = INF, maxY = -INF;
    for(Point& p : points) {
      p.move();
      minX = min(minX, p.x);
      maxX = max(maxX, p.x);
      minY = min(minY, p.y);
      maxY = max(maxY, p.y);
    }

    if(maxY - minY < MAXY) {
      vector<string> grid(maxY - minY + 1, string(maxX - minX + 1, '.'));
      for(Point& p : points) {
        grid[p.y - minY][p.x - minX] = '#';
      }
      for(auto& row : grid) {
        cout << row << endl;
      }
      cout << it << endl;
      cout << endl;
    }
  }
  return 0;
}
