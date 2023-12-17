#include <cstdio>
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
  int cnt = 0;

  string line;
  while(getline(cin, line)) {
    set<string> known;

    bool valid = true;
    int pos = 0, found;
    do {
      found = line.find(' ', pos);
      string word = line.substr(pos, found > 0 ? found - pos : -1);

      if(known.count(word)) { valid = false; break; }
      known.insert(word);
      pos = found + 1;
    } while(found > 0);

    if(valid) cnt++;
  }
  printf("%d\n", cnt);
  return 0;
}
