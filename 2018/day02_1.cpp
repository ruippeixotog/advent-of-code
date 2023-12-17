#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
  string id;
  int x2 = 0, x3 = 0;
  while(getline(cin, id)) {
    unordered_map<char, int> hist;
    for(char ch : id) {
      hist[ch]++;
    }
    bool hasX2 = false, hasX3 = false;
    for(auto entry : hist) {
      if(entry.second == 2) hasX2 = true;
      if(entry.second == 3) hasX3 = true;
    }
    x2 += hasX2; x3 += hasX3;
  }
  printf("%d\n", x2 * x3);
  return 0;
}
