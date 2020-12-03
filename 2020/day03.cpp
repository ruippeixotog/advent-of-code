#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

vector<string> grid;

int checkSlope(int right, int down) {
  int j = 0, cnt = 0;
  for(int i = 0; i < grid.size(); i += down) {
    if(grid[i][j] == '#') cnt++;
    j = (j + right) % grid[0].size();
  }
  return cnt;
}

int main() {
  string line;
  while(getline(cin, line)) {
    grid.push_back(line);
  }
  int res1 = checkSlope(3, 1);
  ll res2 = (ll) checkSlope(1, 1) * checkSlope(3, 1) * checkSlope(5, 1) *
    checkSlope(7, 1) * checkSlope(1, 2);

  printf("%d %lld\n", res1, res2);
  return 0;
}
