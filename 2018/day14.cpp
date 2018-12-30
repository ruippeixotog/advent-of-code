#include <cstdio>
#include <string>

#define NUMR 290431

using namespace std;

string recipes = "37";

bool hasSuffix(string& suffix) {
  if(recipes.size() < suffix.size()) return false;
  if(recipes.size() == suffix.size()) return recipes == suffix;
  return recipes.substr(recipes.length() - suffix.size() - 1).find(suffix) != string::npos;
}

int main() {
  string numrStr = to_string(NUMR);

  int curr1 = 0, curr2 = 1;
  bool found = false;
  for(int i = 0; i < NUMR + 10 || !found; i++) {
    int r1 = recipes[curr1] - '0', r2 = recipes[curr2] - '0', sum = r1 + r2;

    if(sum / 10 > 0) {
      recipes.push_back((char) ('0' + sum / 10));
    }
    recipes.push_back((char) ('0' + sum % 10));

    curr1 = (curr1 + r1 + 1) % (int) recipes.length();
    curr2 = (curr2 + r2 + 1) % (int) recipes.length();
    if(hasSuffix(numrStr)) {
      found = true;
    }
  }
  printf("%s\n", recipes.substr(NUMR, 10).c_str());
  printf("%d\n", (int) recipes.find(to_string(NUMR)));
  return 0;
}
