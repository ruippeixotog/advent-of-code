#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s;
  int cnt = 0;

  while(getline(cin, s)) {
    bool abbaIn = false, abbaOut = false, inHypernet = false;
    int netBegin = 0;

    for(int i = 0; i < s.length(); i++) {
      if(s[i] == '[') { inHypernet = true; netBegin = i + 1; }
      else if(s[i] == ']') { inHypernet = false; netBegin = i + 1; }
      else if(i < netBegin + 3) continue;

      if(s[i] != s[i - 1] && s[i - 3] == s[i] && s[i - 2] == s[i - 1]) {
        (inHypernet ? abbaIn : abbaOut) = true;
      }
    }
    if(abbaOut && !abbaIn) cnt++;
  }
  printf("%d\n", cnt);
  return 0;
}
