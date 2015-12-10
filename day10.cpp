#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string input = "1113222113";
int times = 50;

string next(string& str) {
  stringstream sout;

  char ch = str[0];
  int cnt = 1;

  for(int i = 1; i < str.length(); i++) {
    if(str[i] == ch) cnt++;
    else {
      sout << cnt << ch;
      ch = str[i]; cnt = 1;
    }
  }
  sout << cnt << ch;
  return sout.str();
}

int main() {
  for(int i = 0; i < times; i++) {
    input = next(input);
  }
  cout << input.length() << endl;
  return 0;
}
