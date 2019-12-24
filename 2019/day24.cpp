#include <bitset>
#include <cstdio>
#include <map>
#include <vector>
#include <unordered_set>

#define SZ 5
#define MAXL 250

using namespace std;

int di[] = { 0, -1, 0, 1 };
int dj[] = { 1, 0, -1, 0 };

bool isAlive(const bitset<SZ>& state, int i, int j) {
  return i >= 0 && i < SZ && j >= 0 && j < SZ && state[i * SZ + j];
}

bitset<SZ> runSimple(bitset<SZ> state) {
  unordered_set<bitset<SZ>> seen;

  while(!seen.count(state)) {
    seen.insert(state);

    bitset<SZ> newState;
    for(int i = 0; i < SZ; i++) {
      for(int j = 0; j < SZ; j++) {
        int cnt = 0;
        for(int d = 0; d < 4; d++) {
          cnt += isAlive(state, i + di[d], j + dj[d]);
        }
        newState[i * SZ + j] = cnt == 1 || (!state[i * SZ + j] && cnt == 2);
      }
    }
    state = newState;
  }
  return state;
}

vector<tuple<int, int, int>> neighbors(int i, int j, int d) {
  int i1 = i + di[d], j1 = j + dj[d];
  if(i1 < 0) return {{-1, SZ / 2 - 1, SZ / 2}};
  if(i1 >= SZ) return {{-1, SZ / 2 + 1, SZ / 2}};
  if(j1 < 0) return {{-1, SZ / 2, SZ / 2 - 1}};
  if(j1 >= SZ) return {{-1, SZ / 2, SZ / 2 + 1}};
  if(i1 == SZ / 2 && j1 == SZ / 2) {
    vector<tuple<int, int, int>> res;
    map<int, int> dMap = {{-1, SZ - 1}, {0, -1}, {1, 0}};
    for(int m = 0; m < SZ; m++) {
      i1 = dMap[di[d]], j1 = dMap[dj[d]];
      res.emplace_back(1, i1 >= 0 ? i1 : m, j1 >= 0 ? j1 : m);
    }
    return res;
  }
  return {{0, i1, j1}};
}

int runLayered(bitset<SZ> centralState, int steps) {
  vector<bitset<SZ>> state(MAXL);
  state[MAXL / 2] = centralState;

  int bugCnt = 0;
  while(steps--) {
    vector<bitset<SZ>> newState(MAXL);
    int newBugCnt = 0;

    for(int layer = 1; layer < MAXL - 1; layer++) {
      for(int i = 0; i < SZ; i++) {
        for(int j = 0; j < SZ; j++) {
          if(i == SZ / 2 && j == SZ / 2) continue;

          int cnt = 0;
          for(int d = 0; d < 4; d++) {
            for(auto neighbor : neighbors(i, j, d)) {
              int dl, i1, j1;
              tie(dl, i1, j1) = neighbor;
              cnt += isAlive(state[layer + dl], i1, j1);
            }
          }
          newState[layer][i * SZ + j] =
            cnt == 1 || (!state[layer][i * SZ + j] && cnt == 2);
          newBugCnt += newState[layer][i * SZ + j];
        }
      }
    }
    state = newState;
    bugCnt = newBugCnt;
  }
  return bugCnt;
}

int main() {
  bitset<SZ> state;

  char line[SZ * 2];
  for(int i = 0; i < SZ; i++) {
    fgets(line, sizeof(line), stdin);
    for(int j = 0; j < SZ; j++) {
      if(line[j] == '#') state[i * SZ + j] = true;
    }
  }

  printf("%d\n", (int) runSimple(state).to_ulong());
  printf("%d\n", (int) runLayered(state, 200));
  return 0;
}
