#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

map<string, function<int (int, int)>> ops = {
  { "NOP", [] (int a, int b) { return a; } },
  { "NOT", [] (int a, int b) { return ~a; } },
  { "AND", [] (int a, int b) { return a & b; } },
  { "OR", [] (int a, int b) { return a | b; } },
  { "LSHIFT", [] (int a, int b) { return a << b; } },
  { "RSHIFT", [] (int a, int b) { return a >> b; } }
};

map<string, pair<string, pair<string, string>>> defs;
map<string, int> res;

bool readCmd(string& cmd, string& arg1, string& arg2, string& out) {
  string word;
  if(!(cin >> word)) return false;

  if(word == "NOT") {
    cmd = word; cin >> arg1 >> word; arg2 = "";
  } else {
    arg1 = word; cin >> word;
    if(word == "->") { cmd = "NOP"; arg2 = ""; }
    else { cmd = word; cin >> arg2 >> word; }
  }
  cin >> out;
  return true;
}

int valueOf(string v) {
  try { return stoi(v); }
  catch (...) {
    if(res.count(v)) return res[v];

    auto def = defs[v];
    int arg1 = def.second.first == "" ? 0 : valueOf(def.second.first);
    int arg2 = def.second.second == "" ? 0 : valueOf(def.second.second);
    return res[v] = ops[def.first](arg1, arg2);
  }
}

int main() {
  string cmd, arg1, arg2, out;

  while(readCmd(cmd, arg1, arg2, out)) {
    defs[out] = make_pair(cmd, make_pair(arg1, arg2));
  }
  int a1 = valueOf("a");
  res.clear();
  res["b"] = a1;
  cout << valueOf("a") << endl;
  return 0;
}
