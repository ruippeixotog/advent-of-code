#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Trie {
  map<char, Trie> children;
  bool valid = false;

  void merge(const Trie& oth) {
    valid = valid || oth.valid;
    for(auto& e : oth.children) {
      children[e.first].merge(e.second);
    }
  }

  void extend(const Trie& oth) {
    for(auto& e : children) {
      e.second.extend(oth);
    }
    if(valid) { valid = false; merge(oth); }
  }

  bool matches(string str, int idx = 0) {
    if(idx == str.size()) return valid;
    if(!children.count(str[idx])) return false;
    return children[str[idx]].matches(str, idx + 1);
  }

  int matchesLoop(string str, const int& comb(const int&, const int&)) {
    function<int(Trie&, int)> aux = [&](Trie& curr, int idx = 0) -> int {
      if(idx == str.size()) return curr.valid;
      int res1 = 0, res2 = 0;
      if(curr.valid && (res1 = aux(*this, idx))) res1++;
      if(curr.children.count(str[idx])) {
        res2 = aux(curr.children[str[idx]], idx + 1);
      }
      return !res1 ? res2 : !res2 ? res1 : comb(res1, res2);
    };
    return aux(*this, 0);
  }
};

map<int, char> prim;
map<int, vector<vector<int>>> rules;

map<int, Trie> resolved;

void resolve(int id) {
  if(resolved.count(id)) return;
  auto& trie = resolved[id];
  if(prim.count(id)) {
    trie.children[prim[id]].valid = true;
    return;
  }
  for(auto& andGroup : rules[id]) {
    for(int depRule : andGroup) {
      resolve(depRule);
    }
    Trie tmp = resolved[andGroup[0]];
    for(int i = 1; i < andGroup.size(); i++) {
      tmp.extend(resolved[andGroup[i]]);
    }
    trie.merge(tmp);
  }
}

bool matches2(string& str) {
  for(int i = 1; i < str.size(); i++) {
    int loop42 = resolved[42].matchesLoop(str.substr(0, i), max);
    int loop31 = resolved[31].matchesLoop(str.substr(i), min);
    if(loop31 > 0 && loop42 > loop31) return true;
  }
  return false;
}

vector<string> strSplit(const string& s, const string& delimiter) {
  vector<string> res;
  int last = 0; int next = 0;
  while ((next = s.find(delimiter, last)) != -1) {
    res.push_back(s.substr(last, next - last));
    last = next + delimiter.size();
  }
  res.push_back(s.substr(last));
  return res;
}

int main() {
  string line;
  while(getline(cin, line) && !line.empty()) {
    auto spl = strSplit(line, ": ");
    int id = stoi(spl[0]);
    if(spl[1][0] == '"') { prim[id] = spl[1][1]; continue; }

    for(auto andGroup : strSplit(spl[1], " | ")) {
      rules[id].push_back(vector<int>());
      for(auto term : strSplit(andGroup, " ")) {
        rules[id].rbegin()->push_back(stoi(term));
      }
    }
  }
  resolve(0);
  int res1 = 0, res2 = 0;
  while(getline(cin, line)) {
    res1 += resolved[0].matches(line);
    res2 += matches2(line);
  }
  printf("%d %d\n", res1, res2);
  return 0;
}
