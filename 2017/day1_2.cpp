#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string str; cin >> str;

  int sum = 0;
  for(int i = 0; i < str.length(); i++) {
    if(str[i] == str[(i + str.length() / 2) % str.length()]) {
      sum += str[i] - '0';
    }
  }
  printf("%d\n", sum);
  return 0;
}
