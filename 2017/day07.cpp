#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, int> weights;
map<string, string> parent;
map<string, vector<string>> children;

pair<int, int> calcWeights(string& name) {
  int totalW = weights[name];
  map<int, vector<string>> branchWs;

  for(string& child : children[name]) {
    auto res = calcWeights(child);
    if(res.second != -1) return {-1, res.second};
    branchWs[res.first].push_back(child);
    totalW += res.first;
  }

  if(branchWs.size() > 1) {
    int correct = -1, wrong = -1;
    for(auto e : branchWs) {
      (e.second.size() > 1 ? correct : wrong) = e.first;
    }
    return {-1, weights[branchWs[wrong][0]] + (correct - wrong)};
  }
  return {totalW, -1};
}

int main() {
  char cName[50]; int w;
  while(scanf("%s (%d)", cName, &w) > 0) {
    string name(cName);
    weights[name] = w;

    string chList; getline(cin, chList);
    if(chList.find("->") != string::npos) {
      chList.erase(0, 4);

      int pos = 0;
      do {
        string child = chList.substr(0, pos = chList.find(", "));
        chList.erase(0, pos + 2);

        parent[child] = name;
        children[name].push_back(child);
      } while(pos >= 0);
    }
  }

  string root = weights.begin()->first;
  while(!parent[root].empty()) root = parent[root];
  auto res = calcWeights(root);

  printf("%s %d\n", root.c_str(), res.second);
  return 0;
}
