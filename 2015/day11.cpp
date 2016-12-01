#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string input = "cqjxxyzz";

string next(string str) {
  for(int i = str.length() - 1; i >= 0; i--) {
    str[i]++;
    if(str[i] == ('z' + 1)) { str[i] = 'a'; }
    else break;
  }
  return str;
}

bool isValid(string& str) {
  int ascCnt = 1; bool asc = false;
  bool repState = false; int reps = 0;

  for(int i = 0; i < str.length(); i++) {
    if(str[i] == 'i' || str[i] == 'o' || str[i] == 'l')
      return false;

    if(i > 0) {
      if(str[i] == (str[i - 1] + 1)) {
        if(++ascCnt == 3) asc = true;
      } else {
        ascCnt = 1;
      }

      if(!repState && str[i] == str[i - 1]) {
        reps++; repState = true;
      } else {
        repState = false;
      }
    }
  }
  return asc && reps >= 2;
}

int main() {
  string str = next(input);
  while(!isValid(str)) { str = next(str); }
  cout << str << endl;
  return 0;
}
