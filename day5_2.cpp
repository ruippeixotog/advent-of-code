#include <iostream>
#include <set>
#include <string>

using namespace std;

set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

int main() {
  string str;
  int count = 0;
  while(cin >> str) {
    bool hasMiddle = false, hasDPair = false;
    set<string> seenPairs;

    for(int i = 2; i < str.length(); i++) {
      if(str[i - 2] == str[i]) { hasMiddle = true; }
      if(seenPairs.count(str.substr(i - 1, 2))) { hasDPair = true; }
      seenPairs.insert(str.substr(i - 2, 2));
    }

    if(hasMiddle && hasDPair)
      count++;
  }

  cout << count << endl;
  return 0;
}
