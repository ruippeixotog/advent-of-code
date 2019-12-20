#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

#define MAXN 150
#define MAXD 150
#define INF 0x3f3f3f3f

using namespace std;

int di[] = { -1, 0, 1, 0 };
int dj[] = { 0, 1, 0, -1 };

vector<string> grid;

map<string, pair<int, int>> poi;
map<pair<int, int>, pair<int, int>> portals;
vector<tuple<int, int, int>> adjs[MAXN][MAXN];

bool isOuter(int i, int j) {
  return i == 2 || j == 2 || i == grid.size() - 3 || j == grid[i].size() - 3;
}

void addEndpoint(int i, int j, const string& label) {
  if(poi.count(label)) {
    auto p = poi[label];
    portals[{i, j}] = p;
    portals[p] = {i, j};
    poi.erase(label);
  } else {
    poi[label] = {i, j};
  }
}

void addPortal(int i, int j, bool isHor) {
  int im = isHor, jm = !isHor;
  string label = {grid[i][j], grid[i + im][j + jm]};

  if(i - im >= 0 && j - jm >= 0 && grid[i - im][j - jm] == '.') {
    addEndpoint(i - im, j - jm, label);
  } else {
    addEndpoint(i + 2 * im, j + 2 * jm, label);
  }
}

int bfs(int i0, int j0) {
  bool visited[MAXN][MAXN];
  memset(visited, false, sizeof(visited));

  queue<tuple<int, int, int>> q;
  q.emplace(0, i0, j0);
  visited[i0][j0] = true;
  auto target = poi["ZZ"];

  while(!q.empty()) {
    int dist, i, j;
    tie(dist, i, j) = q.front(); q.pop();

    if(dist > 0 && (portals.count({i, j}) || make_pair(i, j) == target)) {
      adjs[i0][j0].emplace_back(i, j, dist);
    }
    for(int dir = 0; dir < 4; dir++) {
      int i1 = i + di[dir], j1 = j + dj[dir];
      if(grid[i1][j1] == '.' && !visited[i1][j1]) {
        visited[i1][j1] = true;
        q.emplace(dist + 1, i1, j1);
      }
    }
  }
  return -1;
}

int search(int i0, int j0, bool useDepth) {
  bool visited[MAXD][MAXN][MAXN];
  memset(visited, false, sizeof(visited));

  priority_queue<tuple<int, int, int, int>> q;
  q.emplace(0, 0, i0, j0);
  visited[0][i0][j0] = true;
  auto target = make_tuple(0, poi["ZZ"].first, poi["ZZ"].second);

  while(!q.empty()) {
    int dist, depth, i, j;
    tie(dist, depth, i, j) = q.top(); q.pop();
    dist = -dist;

    if(depth < 0) continue;
    if(make_tuple(depth, i, j) == target) {
      return dist;
    }
    for(auto e : adjs[i][j]) {
      int i1, j1, depth1 = depth, edgeDist;
      tie(i1, j1, edgeDist) = e;
      if(portals.count({i1, j1})) {
        tie(i1, j1) = portals[{i1, j1}];
        if(useDepth) depth1 += isOuter(i1, j1) ? 1 : -1;
        edgeDist++;
      }
      q.emplace(-(dist + edgeDist), depth1, i1, j1);
    }
  }
  return -1;
}

int main() {
  string line;
  while(getline(cin, line)) {
    grid.push_back(line);
  }
  for(int i = 0; i < grid.size() - 1; i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      if(isupper(grid[i][j])) {
        if(isupper(grid[i + 1][j])) {
          addPortal(i, j, true);
        }
        if(j + 1 < grid[i].size() && isupper(grid[i][j + 1])) {
          addPortal(i, j, false);
        }
      }
    }
  }
  auto src = poi["AA"];
  bfs(src.first, src.second);
  for(auto e : portals) {
    bfs(e.first.first, e.first.second);
  }

  printf("%d\n", search(src.first, src.second, false));
  printf("%d\n", search(src.first, src.second, true));
  return 0;
}
