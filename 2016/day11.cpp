#include <cstdio>
#include <queue>
#include <set>
#include <vector>

#define GENS 7

using namespace std;

//vector<int> floors[4] = {
//  {-1, -2},
//  {1},
//  {2},
//  {}
//};

vector<int> floors[4] = {
  {1, -1, 2, -2, 6, -6, 7, -7},
  {3, 4, -4, 5, -5},
  {-3},
  {}
};

set<int> visited;
int finalState = 0;

inline int getFloor(int state, int pos) {
  return (state >> (2 * pos)) & 0b11;
}

inline int setFloor(int& state, int pos, int floor) {
  return (state &~ (0b11 << (2 * pos))) | (floor << (2 * pos));
}

bool isFinal(int state) {
  if(!finalState) {
    for(int i = 0; i <= GENS * 2; i++) {
      finalState = setFloor(finalState, i, 3);
    }
  }
  return state == finalState;
}

bool isValid(int state) {
  bool hasM[] = {false, false, false, false};
  bool hasG[] = {false, false, false, false};

  for(int i = 0; i < GENS; i++) {
    int mfloor = getFloor(state, 2 * i);
    int gfloor = getFloor(state, 2 * i + 1);
    hasG[gfloor] = true;
    if(mfloor != gfloor) hasM[mfloor] = true;
  }
  for(int i = 0; i < 4; i++) {
    if(hasM[i] && hasG[i]) return false;
  }
  return true;
}

void neighbors0(int state, int newState, int thisFloor, bool up,
                int k, int taken, queue<int>& q) {

  if(taken == 2 || k == GENS * 2) {
    if(taken > 0 && !visited.count(newState)) {
      visited.insert(newState);
      if(isValid(newState)) q.push(newState);
    }
    return;
  }

  neighbors0(state, newState, thisFloor, up, k + 1, taken, q);

  if(getFloor(state, k) == thisFloor) {
    newState = setFloor(newState, k, thisFloor + (up ? 1 : -1));
    neighbors0(state, newState, thisFloor, up, k + 1, taken + 1, q);
  }
}

void neighbors(int state, queue<int>& q) {
  int thisFloor = getFloor(state, GENS * 2);
  if(thisFloor > 0) {
    int newState = setFloor(state, GENS * 2, thisFloor - 1);
    neighbors0(state, newState, thisFloor, false, 0, 0, q);
  }
  if(thisFloor < 3) {
    int newState = setFloor(state, GENS * 2, thisFloor + 1);
    neighbors0(state, newState, thisFloor, true, 0, 0, q);
  }
}

int bfs(int initial) {
  int depth = 0, count = 1;
  queue<int> q;
  q.push(initial);

  while(!q.empty()) {
    int state = q.front(); q.pop();
    if(isFinal(state)) return depth;
    neighbors(state, q);

    if((--count) == 0) {
      depth++;
      count = q.size();
    }
  }
  return -1;
}

int main() {
  int state = 0;
  for(int i = 0; i < 3; i++) {
    for(int e : floors[i]) {
      if(e < 0) state = state | (i << (4 * (e - 1)));
      else state = state | (i << (4 * (e - 1) + 2));
    }
  }
  int res = bfs(state);
  printf("%d\n", res);
  return 0;
}
