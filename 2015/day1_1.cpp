#include <iostream>
#include <string>

using namespace std;

int main() {
  string s; cin >> s;

  int floor = 0;
  for(int i = 0; i < s.length(); i++) {
    if(s[i] == '(') floor++;
    if(s[i] == ')') floor--;
  }

  cout << floor << endl;
  return 0;
}
