#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

#define T_ELF 0
#define T_GOBLIN 1

using namespace std;

int di[] = { -1, 0, 0, 1 };
int dj[] = { 0, -1, 1, 0 };
char repr[] = {'E', 'G'};

struct Unit {
  int id, row, col, type, atk, hp;
  Unit(int id, int row, int col, int type):
    id(id), row(row), col(col), type(type), atk(3), hp(200) {};
};

struct GameState {
  vector<string> grid;
  vector<Unit> units;
  vector<int> unitCount;
  map<pair<int, int>, int> location;

  GameState(): unitCount(2, 0) {}

  void setAttackPower(int type, int atk) {
    for(Unit& unit : units) {
      if(unit.type == type) unit.atk = atk;
    }
  }

  void attack(Unit& unit, Unit& target) {
    target.hp -= unit.atk;
    if(target.hp <= 0) {
      location.erase({target.row, target.col});
      grid[target.row][target.col] = '.';
      unitCount[target.type]--;
    }
  }

  void move(Unit& unit, int toI, int toJ) {
    grid[unit.row][unit.col] = '.';
    location.erase({unit.row, unit.col});
    unit.row = toI; unit.col = toJ;
    location[{unit.row, unit.col}] = unit.id;
    grid[unit.row][unit.col] = repr[unit.type];
  }

  void render(int round) {
    usleep(50000);
    printf("\033[2J\033[1;1H");
    printf("Round %d\n", round);
    for(string& row : grid) {
      printf("%s\n", row.c_str());
    }
  }

  int inRange(Unit& unit, pair<int, int> at) {
    int best = -1;
    for(int dir = 0; dir < 4; dir++) {
      pair<int, int> pos = {at.first + di[dir], at.second + dj[dir]};
      if(location.count(pos) && units[location[pos]].type != unit.type) {
        Unit& target = units[location[pos]];
        if(best == -1 || units[best].hp > target.hp) {
          best = target.id;
        }
      }
    }
    return best;
  }

  tuple<int, int, int> calcMove(Unit& curr) {
    queue<pair<int, pair<int, int>>> q;
    map<pair<int, int>, pair<int, int>> seen;
    q.push({0, {curr.row, curr.col}});
    seen[{curr.row, curr.col}] = {-1, -1};

    int minSteps = grid.size() * grid[0].size();
    pair<int, int> destPos = {-1, -1};
    int destTarget = -1;

    while(!q.empty() && q.front().first <= minSteps) {
      int steps; pair<int, int> pos;
      tie(steps, pos) = q.front(); q.pop();

      int target = inRange(curr, pos);
      if(target != -1) {
        minSteps = steps;
        if(destPos.first == -1 || pos < destPos) {
          destPos = pos;
          destTarget = steps <= 1 ? target : -1;
        }
      }
      for(int dir = 0; dir < 4; dir++) {
        int i1 = pos.first + di[dir], j1 = pos.second + dj[dir];
        if(grid[i1][j1] != '.' || seen.count({i1, j1})) continue;

        q.push({steps + 1, {i1, j1}});
        seen[{i1, j1}] = steps > 0 ? seen[pos] : make_pair(i1, j1);
      }
    }
    auto movePos = destPos.first == -1 ? make_pair(-1, -1) : seen[destPos];
    return {movePos.first, movePos.second, destTarget};
  }

  bool doTurn(Unit& unit) {
    if(unit.hp <= 0) return true;
    if(unitCount[!unit.type] == 0) return false;

    int toI, toJ, target;
    tie(toI, toJ, target) = calcMove(unit);

    if(toI != -1) {
      move(unit, toI, toJ);
    }
    if(target != -1) {
      attack(unit, units[target]);
    }
    return true;
  }

  pair<int, int> run(bool doRender) {
    for(int round = 1;; round++) {
      vector<int> orderedIds;
      for(auto e : location) {
        orderedIds.push_back(e.second);
      }
      for(auto id : orderedIds) {
        if(!doTurn(units[id])) {
          if(doRender) render(round);
          return {units[id].type, round};
        }
      }
      if(doRender) render(round);
    }
  }
};

void read(GameState& state) {
  string row;
  while(getline(cin, row)) {
    state.grid.push_back(row);
  }
  int unitId = 0;
  for(int i = 0; i < state.grid.size(); i++) {
    for(int j = 0; j < state.grid[i].size(); j++) {
      if(state.grid[i][j] == 'E' || state.grid[i][j] == 'G') {
        int type = state.grid[i][j] == 'E' ? T_ELF: T_GOBLIN;
        state.location[{i, j}] = unitId;
        state.units.emplace_back(unitId++, i, j, type);
        state.unitCount[type]++;
      }
    }
  }
}

int calcOutcome(const GameState& baseState) {
  GameState state = baseState;
  int rounds = state.run(true).second;
  int totalHp = 0;
  for(auto e : state.location) {
    totalHp += state.units[e.second].hp;
  }
  return (rounds - 1) * totalHp;
}

int calcElfAttack(const GameState& baseState) {
  int low = 4, high = 200;
  while(low < high) {
    int mid = (low + high) / 2;
    GameState state = baseState;
    state.setAttackPower(T_ELF, mid);
    int winner = state.run(false).first;
    if(winner == T_ELF && baseState.unitCount[T_ELF] == state.unitCount[T_ELF]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return low;
}

int main() {
  GameState baseState;
  read(baseState);

  int atk = calcElfAttack(baseState);
  GameState moddedState = baseState;
  moddedState.setAttackPower(T_ELF, atk);

  printf("%d %d\n", calcOutcome(baseState), calcOutcome(moddedState));
  return 0;
}
