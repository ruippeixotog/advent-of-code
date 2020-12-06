#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int readGroup(int& cnt1, int& cnt2) {
  map<char, int> hist;
  int n = 0;
  string line;
  while(getline(cin, line) && !line.empty()) {
    for(char ch : line) hist[ch]++;
    n++;
  }
  cnt1 += hist.size();
  for(auto e : hist) {
    cnt2 += e.second == n;
  }
  return !cin.eof();
}

int main() {
  int cnt1 = 0, cnt2 = 0;
  while(readGroup(cnt1, cnt2)) {}
  printf("%d %d\n", cnt1, cnt2);
  return 0;
}
