#include <iostream>
#include <map>

using namespace std;

map<string, int> compounds = {
  { "children", 3 },
  { "cats", 7 },
  { "samoyeds", 2 },
  { "pomeranians", 3 },
  { "akitas", 0 },
  { "vizslas", 0 },
  { "goldfish", 5 },
  { "trees", 3 },
  { "cars", 2 },
  { "perfumes", 1 }
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
    if(compounds[c1] == n1 && compounds[c2] == n2 && compounds[c3] == n3) {
      break;
    }
  }
  cout << i << endl;
  return 0;
}
