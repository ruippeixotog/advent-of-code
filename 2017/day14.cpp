#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#define N 256
#define ROUNDS 64

#define GRID (N / 2)

using namespace std;

bool grid[GRID][GRID];
bool visited[GRID][GRID];

// copy of day10_2.cpp
vector<int> knotHash(string lenghts) {
  lenghts.insert(lenghts.end(), { 17, 31, 73, 47, 23 });

  int list[N];
  for(int i = 0; i < N; i++)
    list[i] = i;

  int curr = 0, skip = 0;
  for(int k = 0; k < ROUNDS; k++) {
    for(int len : lenghts) {
      for(int i = 0; i < len / 2; i++) {
        swap(list[(curr + i) % N], list[(curr + len - i - 1) % N]);
      }
      curr = (curr + len + skip++) % N;
    }
  }

  vector<int> hash(N / 16);
  for(int i = 0; i < N; i += 16) {
    int elem = 0;
    for(int j = 0; j < 16 && i + j < N; j++) {
      elem ^= list[i + j];
    }
    hash[i / 16] = elem;
  }
  return hash;
}

int ffill(int i, int j) {
  if(i < 0 || i >= GRID || j < 0 || j >= GRID || visited[i][j] || !grid[i][j]) {
    return 0;
  }
  visited[i][j] = true;
  return 1 + ffill(i - 1, j) + ffill(i + 1, j) +
    ffill(i, j - 1) + ffill(i, j + 1);
}

int main() {
  string input; cin >> input;
  for(int i = 0; i < GRID; i++) {
    vector<int> hash = knotHash(input + "-" + to_string(i));
    for(int j = 0; j < 16; j++) {
      for(int k = 0; k < 8; k++) {
        grid[i][j * 8 + k] = (hash[j] & (1 << (7 - k))) > 0;
      }
    }
  }
  int cnt = 0, groupCnt = 0;
  for(int i = 0; i < GRID; i++) {
    for(int j = 0; j < GRID; j++) {
      int sz = ffill(i, j);
      if(sz > 0) { cnt += sz; groupCnt++; }
    }
  }
  printf("%d %d\n", cnt, groupCnt);
  return 0;
}
