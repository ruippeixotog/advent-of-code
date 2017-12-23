#include <iostream>
#include <map>
#include <string>

using namespace std;

int di[] = { 0, -1, 0, 1 };
int dj[] = { 1, 0, -1, 0 };

map<int, map<int, char>> grid;

int main() {
  string line; int idx = 0;
  while(getline(cin, line)) {
    for(int i = 0; i < line.length(); i++) {
      grid[idx - line.length() / 2][i - line.length() / 2] = line[i];
    }
    idx++;
  }

  int i = 0, j = 0, d = 1, cnt = 0;
  for(int k = 0; k < 10000000; k++) {
    auto stIt = grid[i].find(j);
    char state = stIt == grid[i].end() ? '.' : stIt->second;

    int dinc; char newState;
    switch(state) {
      case '.': dinc = 1; newState = 'W'; break;
      case 'W': dinc = 0; newState = '#'; break;
      case '#': dinc = 3; newState = 'F'; break;
      default: dinc = 2; newState = '.'; break;
    }
    d = (d + dinc) % 4;
    grid[i][j] = newState;
    if(grid[i][j] == '#') cnt++;
    i += di[d]; j += dj[d];
  }
  cout << cnt << endl;
  return 0;
}
