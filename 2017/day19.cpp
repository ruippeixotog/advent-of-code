#include <iostream>
#include <string>
#include <vector>

using namespace std;

int di[] = { 0, -1, 0, 1 };
int dj[] = { 1, 0, -1, 0 };

vector<string> grid;

void move(int& i, int& j, int d) {
  i += di[d]; j += dj[d];
}

bool validMove(int i, int j, int d) {
  move(i, j, d);
  return i >= 0 && i < grid.size() &&
    j >= 0 && j < grid[0].length() && grid[i][j] != ' ';
}

int main() {
  string line;
  while(getline(cin, line)) {
    grid.push_back(line);
  }

  int startCol = -1;
  for(int i = 0; i < grid[0].length(); i++) {
    if(grid[0][i] != ' ') { startCol = i; break; }
  }

  int cnt = 0; string letters;
  int i = 0, j = startCol, d = 3;
  while(true) {
    cnt++;
    if(grid[i][j] >= 'A' && grid[i][j] <= 'Z') {
      letters.push_back(grid[i][j]);
    }
    if(!validMove(i, j, d)) {
      if(validMove(i, j, (d + 1) % 4)) d = (d + 1) % 4;
      else if(validMove(i, j, (d + 3) % 4)) d = (d + 3) % 4;
      else break;
    }
    move(i, j, d);
  }
  cout << letters << " " << cnt << endl;
  return 0;
}
