#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

char repr[] = {'<', '^', '>', 'v'};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
int dp[] = {-1, 0, 1};

vector<string> grid;

struct Cart {
  int x, y, dir, phase;
  Cart(int _x, int _y, int _dir): x(_x), y(_y), dir(_dir), phase(0) {}

  void move() {
    x += dx[dir]; y += dy[dir];
    char newTrack = grid[y][x];
    if(newTrack == '\\') {
      dir = (dir + 4 + (dx[dir] != 0 ? 1 : -1)) % 4;
    } else if (newTrack == '/') {
      dir = (dir + 4 + (dx[dir] == 0 ? 1 : -1)) % 4;
    } else if (newTrack == '+') {
      dir = (dir + 4 + dp[phase]) % 4;
      phase = (phase + 1) % 3;
    }
  }

  pair<int, int> location() {
    return { y, x };
  }
};

int main() {
  string row;
  while(getline(cin, row)) {
    grid.push_back(row);
  }

  map<pair<int, int>, Cart> carts;
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      for(int dir = 0; dir < 4; dir++) {
        if(grid[i][j] == repr[dir]) {
          Cart c(j, i, dir);
          carts.emplace(c.location(), c);
          break;
        }
      }
    }
  }

  bool firstCrash = true;
  while(carts.size() > 1) {
    queue<Cart> q;
    for(auto e : carts) {
      q.push(e.second);
    }

    while(!q.empty()) {
      Cart c = q.front(); q.pop();
      if(!carts.count(c.location())) {
        continue;
      }
      carts.erase(c.location());
      c.move();

      if(carts.count(c.location())) {
        carts.erase(c.location());
        if(firstCrash) {
          printf("%d,%d\n", c.x, c.y);
          firstCrash = false;
        }
      } else {
        carts.emplace(c.location(), c);
      }
    }
  }
  Cart c = carts.begin()->second;
  printf("%d,%d\n", c.x, c.y);
  return 0;
}
