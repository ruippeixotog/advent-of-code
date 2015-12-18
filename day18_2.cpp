#include <iostream>

#define N 100

using namespace std;

bool grid[N][N], newGrid[N][N];

int neighCount(int i, int j) {
  int cnt = 0;
  if(i > 0) {
    cnt += grid[i - 1][j];
    if(j > 0) cnt += grid[i - 1][j - 1];
    if(j < N - 1) cnt += grid[i - 1][j + 1];
  }
  if(i < N - 1) {
    cnt += grid[i + 1][j];
    if(j > 0) cnt += grid[i + 1][j - 1];
    if(j < N - 1) cnt += grid[i + 1][j + 1];
  }
  if(j > 0) cnt += grid[i][j - 1];
  if(j < N - 1) cnt += grid[i][j + 1];
  return cnt;
}

bool isCorner(int i, int j) {
  return (i == 0 || i == N - 1) && (j == 0 || j == N - 1);
}

int main() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      char ch; cin >> ch;
      grid[i][j] = isCorner(i, j) || ch == '#';
    }
  }

  int onCnt;
  for(int k = 0; k < 100; k++) {
    onCnt = 0;
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
        int ncnt = neighCount(i, j);
        newGrid[i][j] = isCorner(i, j) || ncnt == 3 ||
          (grid[i][j] && ncnt == 2);
        onCnt += newGrid[i][j];
      }
    }
    memcpy(grid, newGrid, sizeof(grid));
  }

  cout << onCnt << endl;
  return 0;
}
