#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  vector<string> rows;
  string line;
  while(getline(cin, line)) {
    rows.push_back(line);
  }
  sort(rows.begin(), rows.end());

  unordered_map<int, int> total;
  unordered_map<int, vector<int>> byMinute;

  int currId = -1, sleepSince = -1;
  for(string& row : rows) {
    int minute, id;
    sscanf(row.c_str(), "[%*d-%*d-%*d %*d:%d] ", &minute);

    if(sscanf(row.c_str(), "%*[^]]] Guard #%d begins shift", &id) == 1) {
      currId = id;
    } else if(sleepSince == -1) {
      sleepSince = minute;
    } else {
      total[currId] += minute - sleepSince;
      byMinute[currId].resize(60, 0);
      for(int mn = sleepSince; mn < minute; mn++) {
        byMinute[currId][mn]++;
      }
      sleepSince = -1;
    }
  }

  int maxId = total.begin()->first, maxMin = 0;
  for(auto& entry : total) {
    if(entry.second > total[maxId]) {
      maxId = entry.first;
    }
  }
  for(int i = 0; i < 60; i++) {
    if(byMinute[maxId][i] > byMinute[maxId][maxMin]) {
      maxMin = i;
    }
  }
  printf("%d\n", maxId * maxMin);

  maxId = total.begin()->first, maxMin = 0;
  for(auto& entry : byMinute) {
    for(int i = 0; i < 60; i++) {
      if(entry.second[i] > byMinute[maxId][maxMin]) {
        maxId = entry.first;
        maxMin = i;
      }
    }
  }
  printf("%d\n", maxId * maxMin);
  return 0;
}
