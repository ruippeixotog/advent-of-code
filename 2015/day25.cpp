#include <iostream>

#define ll long long

using namespace std;

int row = 3010, col = 3019;

ll current = 20151125;

int main() {
  int n = 0;
  for(int i = 2; i < row + col; i++) {
    n += i - 1;
  }
  n += col;

  for(int i = 1; i < n; i++) {
    current = current * 252533 % 33554393; 
  }

  cout << current << endl;
  return 0;
}
