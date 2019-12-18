#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
#include <bitset>

#define MAXN 80
#define KEYS 26
#define RBTS 4
#define INF 0x3f3f3f3f

using namespace std;

typedef bitset<KEYS> State;

int di[] = { -1, 0, 1, 0 };
int dj[] = { 0, 1, 0, -1 };

vector<string> grid;

vector<pair<int, int>> adjs[KEYS * 2 + RBTS];
unordered_map<State, int> seen[RBTS][KEYS * 2 + RBTS];

int getDoor(int i, int j) {
  return grid[i][j] >= 'A' && grid[i][j] <= 'Z' ? grid[i][j] - 'A' : -1;
}

int getKey(int i, int j) {
  return grid[i][j] >= 'a' && grid[i][j] <= 'z' ? grid[i][j] - 'a' : -1;
}

bool isValid(int i, int j) {
  return i >= 0 && i < grid.size() &&
    j >= 0 && j < grid[i].size() && grid[i][j] != '#';
}

void bfs(int i0, int j0, int fromId) {
  bool visited[MAXN][MAXN];
  memset(visited, false, sizeof(visited));

  queue<tuple<int, int, int>> q;
  q.emplace(i0, j0, 0);

  while(!q.empty()) {
    int i, j, dist;
    tie(i, j, dist) = q.front(); q.pop();

    int obj;
    if((obj = getKey(i, j)) >= 0 && obj != fromId) {
      adjs[fromId].emplace_back(obj, dist);
    }
    if((obj = getDoor(i, j)) >= 0 && KEYS + obj != fromId) {
      adjs[fromId].emplace_back(KEYS + obj, dist);
      continue;
    }
    for(int dir = 0; dir < 4; dir++) {
      int i1 = i + di[dir], j1 = j + dj[dir];
      if(isValid(i1, j1) && !visited[i1][j1]) {
        visited[i1][j1] = true;
        q.emplace(i1, j1, dist + 1);
      }
    }
  }
}

int search(vector<int>& poss, State state, int currDist);

int searchTurn(vector<int>& poss, State state, int currDist, int turn) {
  int pos = poss[turn];
  if(seen[turn][pos].count(state) && seen[turn][pos][state] <= currDist) {
    return INF;
  }
  seen[turn][pos][state] = currDist;

  int best = INF;
  for(auto e : adjs[pos]) {
    poss[turn] = e.first;
    if(e.first < KEYS && !state[e.first]) {
      State newState = state;
      newState[e.first] = true;
      best = min(best, search(poss, newState, currDist + e.second));
    } else if(e.first < 2 * KEYS && state[e.first - KEYS]) {
      best = min(best, searchTurn(poss, state, currDist + e.second, turn));
    }
  }
  poss[turn] = pos;
  return best;
}

int search(vector<int>& poss, State state, int currDist) {
  if(state.all()) return currDist;

  int best = INF;
  for(int i = 0; i < poss.size(); i++) {
    best = min(best, searchTurn(poss, state, currDist, i));
  }
  return best;
}

int solve() {
  for(auto& posAdjs : adjs) {
    posAdjs.clear();
  }

  int robotCnt = 0;
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      if(grid[i][j] == '@') {
        bfs(i, j, KEYS * 2 + robotCnt++);
      }
      int obj;
      if((obj = getKey(i, j)) >= 0) bfs(i, j, obj);
      if((obj = getDoor(i, j)) >= 0) bfs(i, j, KEYS + obj);
    }
  }

  for(int i = 0; i < KEYS * 2 + robotCnt; i++) {
    sort(adjs[i].begin(), adjs[i].end(), [](pair<int, int> p1, pair<int, int> p2) {
      if(p1.first < KEYS != p2.first < KEYS) return p1.first < p2.first;
      return p1.second < p2.second;
    });
  }

  vector<int> poss;
  for(int i = 0; i < robotCnt; i++) {
    poss.push_back(KEYS * 2 + i);
    for(int j = 0; j < KEYS * 2 + robotCnt; j++) {
      seen[i][j].clear();
    }
  }
  return search(poss, State(), 0);
}

int main() {
  string line;
  while(getline(cin, line)) {
    grid.push_back(line);
  }
  printf("%d\n", solve());

  for(int i = 39; i <= 41; i++) {
    for(int j = 39; j <= 41; j++) {
      grid[i][j] = i == 40 || j == 40 ? '#' : '@';
    }
  }
  printf("%d\n", solve());

  return 0;
}
