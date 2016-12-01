#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<string, string>> rules;
string input;

set<string> found;

void read() {
  string line; bool isRule = true;
  while(getline(cin, line)) {
    if(line == "") { isRule = false; continue; }

    if(isRule) {
      istringstream sin(line); string from, to;
      sin >> from >> line >> to;
      rules.push_back(make_pair(from, to));
    } else {
      input = line;
    }
  }
}

int main() {
  read();

  for(int i = 0; i < rules.size(); i++) {
    pair<string, string> rule = rules[i];

    int pos = 0;
    while((pos = input.find(rule.first, pos)) >= 0) {
      string output = input;
      found.insert(output.replace(pos, rule.first.length(), rule.second));
      pos++;
    }
  }
  cout << found.size() << endl;
  return 0;
}
