#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MAXN 50
#define MAXM 180
#define POI 8

using namespace std;

typedef tuple<int, int, int> state;

vector<string> grid;
state finalState;

bool visited[MAXN][MAXM][1 << POI];

bool isFinal(state st) {
  // return get<2>(st) == ((1 << POI) - 1);
  return st == finalState;
}

void pushIfValid(int i, int j, int oldPoi, queue<state>& q) {
  if(i >= 0 && j >= 0 && i < grid.size() && j < grid[i].size() && grid[i][j] != '#') {
    int newPoi = grid[i][j] == '.' ? oldPoi : oldPoi | (1 << (grid[i][j] - '0'));

    if(!visited[i][j][newPoi]) {
      visited[i][j][newPoi] = true;
      q.push({i, j, newPoi});
    }
  }
}

void neighbors(int i, int j, int poi, queue<state>& q) {
  pushIfValid(i + 1, j, poi, q); pushIfValid(i - 1, j, poi, q);
  pushIfValid(i, j + 1, poi, q); pushIfValid(i, j - 1, poi, q);
}

int bfs(state initial) {
  int depth = 0, count = 1;
  queue<state> q;
  q.push(initial);

  while(!q.empty()) {
    state st = q.front(); q.pop();
    if(isFinal(st)) return depth;
    neighbors(get<0>(st), get<1>(st), get<2>(st), q);

    if((--count) == 0) {
      depth++;
      count = q.size();
    }
  }
  return -1;
}

int main() {
  string str;
  while(getline(cin, str)) grid.push_back(str);

  int res = -1;
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[i].length(); j++) {
      if(grid[i][j] == '0') {
        finalState = { i, j, (1 << POI) - 1 };
        res = bfs({ i, j, 1 });
        break;
      }
    }
    if(res >= 0) break;
  }
  printf("%d\n", res);
  return 0;
}
