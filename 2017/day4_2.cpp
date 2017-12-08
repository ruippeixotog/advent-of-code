#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<int> getHist(string str) {
  vector<int> hist(26);
  for(char ch : str) hist[ch - 'a']++;
  return hist;
}

int main() {
  int cnt = 0;

  string line;
  while(getline(cin, line)) {
    set<vector<int>> known;

    bool valid = true;
    int pos = 0, found;
    do {
      found = line.find(' ', pos);
      auto word = getHist(line.substr(pos, found > 0 ? found - pos : -1));

      if(known.count(word)) { valid = false; break; }
      known.insert(word);
      pos = found + 1;
    } while(found > 0);

    if(valid) cnt++;
  }
  printf("%d\n", cnt);
  return 0;
}
