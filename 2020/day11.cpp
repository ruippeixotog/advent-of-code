#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int di[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dj[] = {0, 1, 1, 1, 0, -1, -1, -1};

vector<string> initialGrid;

bool isValid(int i, int j) {
  return i >= 0 && i < initialGrid.size() &&
    j >= 0 && j < initialGrid[0].size();
}

pair<int, int> adj1(int i, int j, int d) {
  return {i + di[d], j + dj[d]};
}

pair<int, int> adj2(int i, int j, int d) {
  int i1 = i + di[d], j1 = j + dj[d];
  while(isValid(i1, j1) && initialGrid[i1][j1] == '.') {
    i1 += di[d], j1 += dj[d];
  }
  return {i1, j1};
}

int solve(pair<int, int> adjFunc(int, int, int), int minOcc) {
  vector<string> grid = initialGrid;

  bool updated = true;
  while(updated) {
    updated = false;

    vector<string> newGrid = grid;    
    for(int i = 0; i < grid.size(); i++) {
      for(int j = 0; j < grid[0].size(); j++) {
        map<char, int> cnts;
        for(int d = 0; d < 8; d++) {
          auto adj = adjFunc(i, j, d);
          if(isValid(adj.first, adj.second)) {
            cnts[grid[adj.first][adj.second]]++;
          }
        }
        if(grid[i][j] == 'L' && cnts['#'] == 0) {
          newGrid[i][j] = '#'; updated = true;
        }
        if(grid[i][j] == '#' && cnts['#'] >= minOcc) {
          newGrid[i][j] = 'L'; updated = true;
        }
      }
    }
    grid = newGrid;
  }
  int cnt = 0;
  for(auto row : grid) {
    for(char cell : row) {
      if(cell == '#') cnt++;
    }
  }
  return cnt;
}

int main() {
  string line;
  while(getline(cin, line)) {
    initialGrid.push_back(line);
  }
  int res1 = solve(adj1, 4);
  int res2 = solve(adj2, 5);
  printf("%d %d\n", res1, res2);
  return 0;
}
