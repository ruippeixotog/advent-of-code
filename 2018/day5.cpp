#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

string react(string str, char ignore = 0) {
  bool changed = true;
  while(changed) {
    changed = false;

    string last = str;
    last.push_back('-');
    str.clear();

    for(int i = 1; i < last.length(); i++) {
      if(last[i - 1] == ignore || last[i - 1] == ignore + ('a' - 'A')) {
        continue;
      }
      if(abs((int) (last[i - 1] - last[i])) == ('a' - 'A')) {
        changed = true;
        i++;
      } else {
        str.push_back(last[i - 1]);
      }
    }
  }
  return str;
}

int main() {
  string str; cin >> str;
  printf("%d\n", (int) react(str).length());

  int bestLen = (int) str.length();
  for(char ch = 'A'; ch <= 'Z'; ch++) {
    bestLen = min(bestLen, (int) react(str, ch).length());
  }
  printf("%d\n", bestLen);
  return 0;
}
