#include <iostream>
#include <string>

using namespace std;

int main() {
  string s; cin >> s;

  int i, floor = 0;
  for(i = 0; i < s.length(); i++) {
    if(s[i] == '(') floor++;
    if(s[i] == ')') {
      if(--floor == -1) break;
    }
  }

  cout << (i + 1) << endl;
  return 0;
}
