#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> Coord;

map<char, Coord> step = {{'N', {-1, 0}}, {'E', {0, 1}}, {'S', {1, 0}}, {'W', {0, -1}}};

map<Coord, vector<char>> adjs;
map<Coord, int> dists;

Coord operator+(const Coord& a, const Coord& b) {
  return {a.first + b.first, a.second + b.second};
}

void bfs(Coord pos0) {
  queue<pair<Coord, int>> q;
  q.emplace(pos0, 0);

  while(!q.empty()) {
    auto e = q.front();
    q.pop();
    if(!dists.count(e.first)) {
      dists[e.first] = e.second;
      for(char dir : adjs[e.first]) {
        q.emplace(e.first + step[dir], e.second + 1);
      }
    }
  }
}

int main() {
  string line;
  getline(cin, line);

  pair<int, int> pos = {0, 0};
  stack<pair<int, int>> st;
  for (int i = 1; i < line.size() - 1; i++) {
    switch (line[i]) {
      case '(': st.push(pos); break;
      case ')': st.pop(); break;
      case '|': pos = st.top(); break;
      default:
        adjs[pos].push_back(line[i]);
        pos = pos + step[line[i]];
    }
  }

  bfs({0, 0});
  int best = 0, numFar = 0;
  for(auto e : dists) {
    best = max(best, e.second);
    if(e.second >= 1000) numFar++;
  }
  printf("%d %d\n", best, numFar);
  return 0;
}
