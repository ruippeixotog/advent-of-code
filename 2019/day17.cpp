#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include "lib/intcode.cpp"

using namespace std;

int di[] = { -1, 0, 1, 0 };
int dj[] = { 0, 1, 0, -1 };
map<char, int> dirRepr = {{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};

vector<string> grid;

string path, mainCmd;
vector<string> funcs;

int alignmentSum() {
  int sum = 0;
  for(int i = 1; i < (int) grid.size() - 1; i++) {
    for(int j = 1; j < (int) grid[i].length() - 1; j++) {
      int param = grid[i][j] != '#' ? 0 : i * j;
      for(int dir = 0; dir < 4; dir++) {
        if(grid[i + di[dir]][j + dj[dir]] != '#') {
          param = 0;
        }
      }
      sum += param;
    }
  }
  return sum;
}

bool isScaffold(int i, int j) {
  return i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size() &&
    grid[i][j] == '#';
}

void buildFullPath() {
  int ri = -1, rj = -1, dir = -1;
  for(int i = 0; i < grid.size() && dir == -1; i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      if(dirRepr.count(grid[i][j])) {
        ri = i; rj = j; dir = dirRepr[grid[i][j]];
        break;
      }
    }
  }
  while(true) {
    int lDir = (dir + 3) % 4, rDir = (dir + 1) % 4;
    if(isScaffold(ri + di[lDir], rj + dj[lDir])) dir = lDir;
    else if(isScaffold(ri + di[rDir], rj + dj[rDir])) dir = rDir;
    else break;

    int steps = 0;
    while(isScaffold(ri + di[dir], rj + dj[dir])) {
      steps++;
      ri += di[dir]; rj += dj[dir];
    }
    if(!path.empty()) path.push_back(',');
    path.append({dir == lDir ? 'L' : 'R', ','});
    path += to_string(steps);
  }
}

bool findCmdsAndFuncs(int idx) {
  if(idx >= path.size()) return true;

  for(int i = 0; i < funcs.size(); i++) {
    if(path.find(funcs[i], idx) == idx) {
      if(!mainCmd.empty()) mainCmd.push_back(',');
      mainCmd.push_back('A' + i);
      if(findCmdsAndFuncs(idx + funcs[i].size() + 1)) {
        return true;
      }
      mainCmd.pop_back();
      if(!mainCmd.empty()) mainCmd.pop_back();
      break;
    }
  }
  if(funcs.size() >= 3) {
    return false;
  }
  int pos = idx - 1;
  while ((pos = path.find(',', pos + 1)) != string::npos && pos < idx + 20) {
    funcs.push_back(path.substr(idx, pos - idx));

    if(!mainCmd.empty()) mainCmd.push_back(',');
    mainCmd.push_back('A' + funcs.size() - 1);
    if(findCmdsAndFuncs(pos + 1)) {
      return true;
    }
    mainCmd.pop_back();
    if(!mainCmd.empty()) mainCmd.pop_back();
    funcs.pop_back();
  }
  return false;
}

int main() {
  Prog baseProg;
  readProg(baseProg);

  ProgState state(baseProg);
  runProgState(state);
  readGrid(state, grid);
  printf("%d\n", alignmentSum());

  buildFullPath();
  findCmdsAndFuncs(0);

  ProgState state2(baseProg);
  state2.prog[0] = 2;
  runInteractive(state2, {
    {"Main:", mainCmd},
    {"Function A:", funcs[0]},
    {"Function B:", funcs[1]},
    {"Function C:", funcs[2]},
    {"Continuous video feed?", "n"}
  });
  return 0;
}
