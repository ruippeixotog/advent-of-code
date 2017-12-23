#include <iostream>
#include <string>
#include <vector>

using namespace std;

int di[] = { 0, -1, 0, 1 };
int dj[] = { 1, 0, -1, 0 };

vector<string> grid(20000, string(20000, '.'));

int main() {
  string line; int idx = 0;
  while(getline(cin, line)) {
    grid[10000 - line.length() / 2 + idx].replace(
      10000 - line.length() / 2, line.size(), line);
    idx++;
  }

  int i = 10000, j = 10000, d = 1, cnt = 0;
  for(int k = 0; k < 10000; k++) {
    d = (d + (grid[i][j] == '#' ? 3 : 1)) % 4;
    grid[i][j] = grid[i][j] == '#' ? '.' : '#';
    if(grid[i][j] == '#') cnt++;
    i += di[d]; j += dj[d];
  }
  cout << cnt << endl;
  return 0;
}
