#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define IMG_SZ 12
#define TILE_SZ 10
#define MON_SZ_I 3
#define MON_SZ_J 20

using namespace std;

typedef long long ll;

vector<pair<int, int>> monsterDeltas = {
  {1, 0}, {2, 1}, {2, 4}, {1, 5}, {1, 6}, {2, 7}, {2, 10}, {1, 11}, {1, 12},
  {2, 13}, {2, 16}, {1, 17}, {0, 18}, {1, 18}, {1, 19}
};

map<int, vector<string>> tiles;

vector<pair<vector<string>, int>> allTiles;
map<pair<int, int>, int> links;

void flipX(vector<string>& tile) {
  for(int i = 0; i < TILE_SZ; i++) {
    reverse(tile[i].begin(), tile[i].end());
  }
}

void rotate90(vector<string>& tile) {
  for(int i = 0; i < TILE_SZ / 2; i++) {
    for(int j = i; j < TILE_SZ - i - 1; j++) {
      int tmp = tile[i][j];
      tile[i][j] = tile[TILE_SZ - j - 1][i];
      tile[TILE_SZ - j - 1][i] = tile[TILE_SZ - i - 1][TILE_SZ - j - 1];
      tile[TILE_SZ - i - 1][TILE_SZ - j - 1] = tile[j][TILE_SZ - i - 1];
      tile[j][TILE_SZ - i - 1] = tmp;
    }
  }
}

string getBorder(const vector<string>& tile, int dir) {
  string res;
  for(int i = 0; i < TILE_SZ; i++) {
    switch(dir) {
      case 0: res.push_back(tile[0][i]); break;
      case 1: res.push_back(tile[i][TILE_SZ - 1]); break;
      case 2: res.push_back(tile[TILE_SZ - 1][TILE_SZ - i - 1]); break;
      case 3: res.push_back(tile[TILE_SZ - i - 1][0]); break;
    }
  }
  return res;
}

void genAllTiles() {
  for(auto& e : tiles) {
    for(int d = 0; d < 4; d++, rotate90(e.second)) {
      allTiles.push_back({e.second, e.first});
    }
    flipX(e.second);
    for(int d = 0; d < 4; d++, rotate90(e.second)) {
      allTiles.push_back({e.second, e.first});
    }
    flipX(e.second);
  }
}

void link() {
  for(int i = 0; i < allTiles.size(); i++) {
    for(int d = 0; d < 4; d++) {
      string bi = getBorder(allTiles[i].first, d);
      for(int j = 0; j < allTiles.size(); j++) {
        string bj = getBorder(allTiles[j].first, (d + 2) % 4);
        reverse(bj.begin(), bj.end());

        if(allTiles[i].second != allTiles[j].second && bi == bj) {
          links[{i, d}] = j;
          break;
        }
      }
    }
  }
}

int findSeaMonsters(int cornerId) {
  auto getCell = [](int tileID, int i, int j) {
    while(i >= TILE_SZ - 2) { tileID = links[{tileID, 2}]; i -= TILE_SZ - 2; }
    while(j >= TILE_SZ - 2) { tileID = links[{tileID, 1}]; j -= TILE_SZ - 2; }
    return allTiles[tileID].first[i + 1][j + 1];
  };

  int cnt = 0;
  for(int i = 0; i < IMG_SZ * (TILE_SZ - 2) - MON_SZ_I; i++) {
    for(int j = 0; j < IMG_SZ * (TILE_SZ - 2) - MON_SZ_J; j++) {
      bool found = true;
      for(auto& md : monsterDeltas) {
        if(getCell(cornerId, i + md.first, j + md.second) != '#') {
          found = false;
        }
      }
      cnt += found;
    }
  }
  return cnt;
}

int main() {
  string line;
  while(getline(cin, line) && !line.empty()) {
    int id; sscanf(line.c_str(), "Tile %d:", &id);
    
    while(getline(cin, line) && !line.empty()) {
      tiles[id].push_back(line);
    }
  }
  genAllTiles();
  link();

  int totalHash = 0;
  for(auto& e : tiles) {
    for(int i = 1; i < TILE_SZ - 1; i++) {
      for(int j = 1; j < TILE_SZ - 1; j++) {
        totalHash += e.second[i][j] == '#';
      }
    }
  }
  ll res1 = 1; int res2 = 0;
  set<int> corners;
  for(int i = 0; i < allTiles.size(); i++) {
    if(!links.count({i, 0}) && !links.count({i, 3})) {
      int sm = findSeaMonsters(i);
      if(sm) res2 = totalHash - sm * monsterDeltas.size();

      if(!corners.count(allTiles[i].second)) {
        res1 *= allTiles[i].second;
        corners.insert(allTiles[i].second);
      }
    }
  }
  printf("%lld %d\n", res1, res2);
  return 0;
}
