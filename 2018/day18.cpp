#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int di[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dj[] = {0, 1, 1, 1, 0, -1, -1, -1};

using namespace std;

map<char, int> adjCounts(const vector<string>& grid, int i, int j) {
  map<char, int> hist;
  for(int d = 0; d < 8; d++) {
    int i1 = i + di[d], j1 = j + dj[d];
    if(i1 >= 0 && i1 < grid.size() && j1 >= 0 && j1 < grid[0].size()) {
      hist[grid[i1][j1]]++;
    }
  }
  return hist;
}

void update(vector<string>& grid) {
  vector<string> newGrid = grid;
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      auto cnts = adjCounts(grid, i, j);
      switch(grid[i][j]) {
        case '.':
          if(cnts['|'] >= 3) newGrid[i][j] = '|';
          break;
        case '|':
          if(cnts['#'] >= 3) newGrid[i][j] = '#';
          break;
        case '#':
          if(!cnts['|'] || !cnts['#']) newGrid[i][j] = '.';
          break;
      }
    }
  }
  grid = newGrid;
}

int solve(const vector<string>& initialGrid, int iters) {
  vector<vector<string>> mem;
  map<vector<string>, int> revIdx;

  vector<string> grid = initialGrid;
  for(int i = mem.size(); i < iters; i++) {
    revIdx[grid] = mem.size();
    mem.push_back(grid);
    update(grid);

    if(revIdx.count(grid)) {
      int cycleSize = i - revIdx[grid] + 1;
      grid = mem[revIdx[grid] + (iters - i - 1) % cycleSize];
      break;
    }
  }

  map<char, int> hist;
  for(auto row : grid) {
    for(char cell : row) {
      hist[cell]++;
    }
  }
  return hist['|'] * hist['#'];
}

int main() {
  vector<string> initialGrid;
  string line;
  while(getline(cin, line)) {
    initialGrid.push_back(line);
  }
  int res1 = solve(initialGrid, 10);
  int res2 = solve(initialGrid, 1000000000);
  printf("%d %d\n", res1, res2);
  return 0;
}
