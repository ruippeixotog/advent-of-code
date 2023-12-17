#include <iostream>
#include <set>
#include <string>
#include <utility>

using namespace std;

set<pair<int, int> > visited;

int main() {
  string s; cin >> s;

  int row[] = {0, 0}, col[] = {0, 0}, count = 1;
  visited.insert(make_pair(0, 0));

  for(int i = 0; i < s.length(); i++) {
    int k = i % 2;
    switch(s[i]) {
      case '^': row[k]++; break;
      case 'v': row[k]--; break;
      case '<': col[k]--; break;
      case '>': col[k]++; break;
    }
    if(visited.insert(make_pair(row[k], col[k])).second)
      count++;
  }

  cout << count << endl;
  return 0;
}
