#include <cstdio>
#include <iostream>
#include <string>

#define ROWS 400000

using namespace std;

int main() {
  string str; getline(cin, str);

  int cnt = 0;
  for(int i = 0; i < str.length(); i++)
    cnt += str[i] == '.';

  for(int k = 1; k < ROWS; k++) {
    string next;
    for(int i = 0; i < str.length(); i++) {
      bool t1 = i != 0 && str[i - 1] == '^';
      bool t2 = str[i] == '^';
      bool t3 = i != str.length() - 1 && str[i + 1] == '^';

      bool t = (t1 && t2 && !t3) || (!t1 && t2 && t3) ||
               (t1 && !t2 && !t3) || (!t1 && !t2 && t3);
      next.push_back(t ? '^' : '.');
      cnt += !t;
    }
    str = next;
  }
  printf("%d\n", cnt);
  return 0;
}
