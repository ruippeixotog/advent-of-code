#include <cstdio>
#include <map>
#include <set>
#include <vector>

#define WORKERS 5
#define MINT 60

using namespace std;

set<char> steps;
map<char, set<char>> deps;

set<char> available;

void finishAndScan(char step) {
  for(char s : steps) {
    deps[s].erase(step);
    if(deps[s].empty()) {
      available.insert(s);
    }
  }
  for(char s : available) {
    steps.erase(s);
  }
}

int main() {
  char a1, a2;
  while(scanf("Step %c must be finished before step %c can begin.\n", &a1, &a2) == 2) {
    steps.insert(a1);
    steps.insert(a2);
    deps[a2].insert(a1);
  }

  map<int, vector<char>> events;
  events[0].push_back('_');
  int workers = WORKERS - 1, currT = 0;
  while(!events.empty()) {
    auto ev = *events.begin();
    events.erase(events.begin());

    currT = ev.first;
    for(char step : ev.second) {
      finishAndScan(step);
      workers++;
    }

    while(workers > 0 && !available.empty()) {
      char next = *available.begin();
      events[currT + MINT + (next - 'A') + 1].push_back(next);
      available.erase(next);
      workers--;
    }
  }
  printf("%d\n", currT);
  return 0;
}
