#include <iostream>
#include <set>
#include <string>
#include <utility>

using namespace std;

set<pair<int, int> > visited;

int main() {
  string s; cin >> s;

  int row = 0, col = 0, count = 1;
  visited.insert(make_pair(0, 0));

  for(int i = 0; i < s.length(); i++) {
    switch(s[i]) {
      case '^': row++; break;
      case 'v': row--; break;
      case '<': col--; break;
      case '>': col++; break;
    }
    if(visited.insert(make_pair(row, col)).second)
      count++;
  }

  cout << count << endl;
  return 0;
}
