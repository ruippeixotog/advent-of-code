#include <cstdio>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
  set<char> steps;
  map<char, set<char>> deps;

  char a1, a2;
  while(scanf("Step %c must be finished before step %c can begin.\n", &a1, &a2) == 2) {
    steps.insert(a1);
    steps.insert(a2);
    deps[a2].insert(a1);
  }

  string order;
  while(!steps.empty()) {
    for(char step : steps) {
      if(!deps[step].empty()) {
        continue;
      }
      order.push_back(step);
      steps.erase(step);
      for(auto& e : deps) {
        e.second.erase(step);
      }
      break;
    }
  }
  printf("%s\n", order.c_str());
  return 0;
}
