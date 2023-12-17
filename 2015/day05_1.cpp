#include <iostream>
#include <set>
#include <string>

using namespace std;

set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
set<string> forbidden = {"ab", "cd", "pq", "xy"};

int main() {
  string str;
  int count = 0;
  while(cin >> str) {
    bool hasDouble = false, hasForbid = false;
    int vowelCount = 0;

    for(int i = 0; i < str.length(); i++) {
      if(i > 0) {
        if(str[i] == str[i - 1]) { hasDouble = true; }
        if(forbidden.count(str.substr(i - 1, 2))) { hasForbid = true; break; }
      }
      if(vowels.count(str[i])) vowelCount++;
    }

    if(hasDouble && !hasForbid && vowelCount >= 3)
      count++;
  }

  cout << count << endl;
  return 0;
}
