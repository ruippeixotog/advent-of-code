#include <functional>
#include <iostream>
#include <map>

using namespace std;

map<string, function<bool (int)>> compoundPreds = {
  { "children", [] (int a) { return a == 3; } },
  { "cats", [] (int a) { return a > 7; } },
  { "samoyeds", [] (int a) { return a == 2; } },
  { "pomeranians", [] (int a) { return a < 3; } },
  { "akitas", [] (int a) { return a == 0; } },
  { "vizslas", [] (int a) { return a == 0; } },
  { "goldfish", [] (int a) { return a < 5; } },
  { "trees", [] (int a) { return a > 3; } },
  { "cars", [] (int a) { return a == 2; } },
  { "perfumes", [] (int a) { return a == 1; } }
};

bool readEntry(int& i, string& c1, int& n1, string& c2, int& n2, string& c3, int& n3) {
  char c1c[50], c2c[50], c3c[50];
  int res = scanf("Sue %d: %[^:]: %d, %[^:]: %d, %[^:]: %d\n",
    &i, c1c, &n1, c2c, &n2, c3c, &n3);
  c1 = c1c; c2 = c2c; c3 = c3c;
  return res > 0;
}

int main() {
  string c1, c2, c3; int i, n1, n2, n3;
  while(readEntry(i, c1, n1, c2, n2, c3, n3)) {
    if(compoundPreds[c1](n1) && compoundPreds[c2](n2) && compoundPreds[c3](n3)) {
      break;
    }
  }
  cout << i << endl;
  return 0;
}
