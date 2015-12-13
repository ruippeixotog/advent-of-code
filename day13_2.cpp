#include <cstdio>
#include <iostream>
#include <map>
#include <string>

#define MAXN 10

using namespace std;

map<string, int> ids;
int graph[MAXN][MAXN];

bool readLine(string& from, string& to, int& value) {
  if(!(cin >> from)) return false;

  char sign[5];
  scanf(" would %s %d happiness units by sitting next to ", sign, &value);
  cin >> to;

  if(string(sign) == "lose") value = -value;
  to = to.substr(0, to.length() - 1);
  return true;
}

int getOrAdd(string& name) {
  if(ids.count(name)) return ids[name];
  int id = ids[name] = ids.size();
  return id;
}

bool chosen[MAXN];

int dfs(int k, int value, int last, int first) {
  if(k == ids.size()) {
    return value + graph[first][last] + graph[last][first];
  }

  int best = 0;
  for(int i = 0; i < ids.size(); i++) {
    if(chosen[i]) continue;
    chosen[i] = true;
    int newValue = value + graph[last][i] + graph[i][last];
    best = max(best, dfs(k + 1, newValue, i, first));
    chosen[i] = false;
  }
  return best;
}

int main() {
  string from, to; int value;

  ids["me"] = 0;
  while(readLine(from, to, value)) {
    int p1 = getOrAdd(from);
    int p2 = getOrAdd(to);
    graph[p1][p2] = value;
  }

  int best = 0;
  for(int i = 0; i < ids.size(); i++) {
    chosen[i] = true;
    best = max(best, dfs(1, 0, i, i));
    chosen[i] = false;
  }

  cout << best << endl;
  return 0;
}
