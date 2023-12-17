#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

bool abaFound[26][26], babFound[26][26];

int main() {
  string s;
  int cnt = 0;

  while(getline(cin, s)) {
    bool inHypernet = false;
    int netBegin = 0;

    memset(abaFound, false, sizeof(abaFound));
    memset(babFound, false, sizeof(babFound));

    for(int i = 0; i < s.length(); i++) {
      if(s[i] == '[') { inHypernet = true; netBegin = i + 1; }
      else if(s[i] == ']') { inHypernet = false; netBegin = i + 1; }
      else if(i < netBegin + 2) continue;

      if(s[i] != s[i - 1] && s[i] == s[i - 2]) {
        auto thisFound = inHypernet ? babFound : abaFound;
        auto otherFound = inHypernet ? abaFound : babFound;

        if(otherFound[s[i - 1] - 'a'][s[i] - 'a']) { cnt++; break; }
        thisFound[s[i] - 'a'][s[i - 1] - 'a'] = true;
      }
    }
  }
  printf("%d\n", cnt);
  return 0;
}
