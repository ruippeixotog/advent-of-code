#include <cstdio>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

const regex inputFmt = regex("^([a-z]+ [a-z]+) bags contain (.*)");
const regex inputPartFmt = regex("([0-9]+) ([a-z]+ [a-z]+) bags?[,.]");

map<string, vector<pair<string, int>>> adjs;

bool find(string source, string target) {
  if(source == target) return true;
  for(auto e : adjs[source]) {
    if(find(e.first, target)) return true;
  }
  return false;
}

int count(string source) {
  int cnt = 0;
  for (auto e : adjs[source]) {
    cnt += e.second * (1 + count(e.first));
  }
  return cnt;
}

int main() {
  vector<string> types;
  string line; smatch m;
  while(getline(cin, line)) {
    if(regex_search(line, m, inputFmt)) {
      types.push_back(m.str(1));
      string parts = m.str(2);
      auto partsIt = sregex_iterator(parts.begin(), parts.end(), inputPartFmt);
      for(; partsIt != sregex_iterator(); partsIt++) {
        adjs[m.str(1)].emplace_back((*partsIt)[2], stoi((*partsIt)[1]));
      }
    }
  }
  
  int cnt1 = 0;
  for(string type : types) {
    if(type != "shiny gold") {
      cnt1 += find(type, "shiny gold");
    }
  }
  printf("%d %d\n", cnt1, count("shiny gold"));
  return 0;
}
