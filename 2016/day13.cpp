#include <cstdio>
#include <queue>
#include <set>
#include <utility>

#define FN 1352

using namespace std;

pair<int, int> initialPos = {1, 1};

//pair<int, int> finalPos = {31, 39};
//int maxDepth = 10000000;
pair<int, int> finalPos = {-1, -1};
int maxDepth = 50;

set<pair<int, int>> visited;

bool isWall(int i, int j) {
  int a = i * i + 3 * i + 2 * i * j + j + j * j + FN;
  int bits = 0;
  while(a != 0) { bits += a & 1; a >>= 1; }
  return bits % 2 == 1;
}

void pushIfValid(int i, int j, queue<pair<int, int>>& q) {
  if(i >= 0 && j >= 0 && !isWall(i, j) && !visited.count({i, j})) {
    visited.insert({i, j});
    q.push({i, j});
  }
}

void neighbors(int i, int j, queue<pair<int, int>>& q) {
  pushIfValid(i + 1, j, q); pushIfValid(i - 1, j, q);
  pushIfValid(i, j + 1, q); pushIfValid(i, j - 1, q);
}

int bfs() {
  int depth = 0, count = 1;
  queue<pair<int, int>> q;
  q.push(initialPos);

  while(!q.empty() && depth < maxDepth) {
    auto pos = q.front(); q.pop();
    if(pos == finalPos) return depth;
    neighbors(pos.first, pos.second, q);

    if((--count) == 0) { depth++; count = q.size(); }
  }
  return -1;
}

int main() {
  printf("%d\n", bfs());
  printf("%lu\n", visited.size());
  return 0;
}
