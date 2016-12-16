#include <iostream>
#include <string>

#define LEN 35651584

using namespace std;

string input = "01000100010010111";

string rev(string& str) {
  string reversed;
  for(int i = str.length() - 1; i >= 0; i--)
    reversed += str[i] == '0' ? '1' : '0';
  return reversed;
}

string checksum(string& str) {
  string sum;
  for(int i = 0; i < str.length(); i += 2)
    sum += str[i] == str[i + 1] ? '1' : '0';
  return sum;
}

int main() {
  while(input.length() < LEN) {
    input = input + "0" + rev(input);
  }
  input.erase(LEN);
  while(input.length() % 2 == 0) {
    input = checksum(input);
  }
  cout << input << endl;
  return 0;
}
