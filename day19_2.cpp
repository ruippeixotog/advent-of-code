#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<string, string>> rules;
string input;

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

bool ruleCompare(pair<string, string>& rule1, pair<string, string>& rule2) {
  return rule1.second.length() > rule2.second.length();
}

int main() {
  read();
  
  sort(rules.begin(), rules.end(), ruleCompare);

  int count = 0;
  while(input != "e") {
    for(int i = 0; i < rules.size(); i++) {
      pair<string, string> rule = rules[i];

      int pos = input.find(rule.second, 0);
      if(pos >= 0) {
        input.replace(pos, rule.second.length(), rule.first);
        count++;
        break;
      }
    }
  }

  cout << count << endl;
  return 0;
}
