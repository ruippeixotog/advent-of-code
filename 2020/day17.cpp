#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void fillCube(vector<vector<int>>& neighs, vector<int>& pos, int k = 0) {
  if(k == pos.size()) { neighs.push_back(pos); return; }

  int base = pos[k];
  for(int d = -1; d <= 1; d++) {
    pos[k] = base + d;
    fillCube(neighs, pos, k + 1);
  }
  pos[k] = base;
}

int solve(set<vector<int>>& grid, int its) {
  for(int k = 0; k < its; k++) {
    set<vector<int>> newGrid;
    
    for(auto basePos : grid) {
      vector<vector<int>> cube;
      fillCube(cube, basePos);

      for(auto pos : cube) {
        vector<vector<int>> adjs;
        fillCube(adjs, pos);

        int activeAdjs = 0;
        for(auto adj : adjs) {
          if(adj != pos && grid.count(adj)) activeAdjs++;
        }
        if(activeAdjs == 3 || (activeAdjs == 2 && grid.count(pos))) {
          newGrid.emplace(pos);
        }
      }
    }
    grid = newGrid;
  }
  return grid.size();
}

int main() {
  set<vector<int>> grid3D, grid4D;
  string line;
  for(int i = 0; getline(cin, line); i++) {
    for(int j = 0; j < line.size(); j++) {
      if(line[j] == '#') {
        grid3D.insert({i, j, 0});
        grid4D.insert({i, j, 0, 0});
      }
    }
  }
  printf("%d %d\n", solve(grid3D, 6), solve(grid4D, 6));
  return 0;
}
