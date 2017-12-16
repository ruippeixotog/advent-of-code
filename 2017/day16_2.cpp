#include <cstdio>
#include <string>
#include <set>
#include <tuple>
#include <vector>

#define PROGS 16
#define REPS 1000000000

using namespace std;

vector<tuple<int, int, int>> danceSteps;

void doDance(string& progs) {
  for(auto step : danceSteps) {
    int arg1 = get<1>(step), arg2 = get<2>(step);
    switch(get<0>(step)) {
      case 0:
        progs = progs.substr(PROGS - arg1) + progs.substr(0, PROGS - arg1);
        break;
      case 1:
        swap(progs[arg1], progs[arg2]);
        break;
      case 2:
        arg1 = progs.find(arg1); arg2 = progs.find(arg2);
        swap(progs[arg1], progs[arg2]);
        break;
    }
  }
}

int main() {
  while(true) {
    int arg1, arg2;
    if(scanf("s%d,", &arg1) == 1) {
      danceSteps.push_back(make_tuple(0, arg1, 0));
    } else if(scanf("x%d/%d,", &arg1, &arg2) == 2) {
      danceSteps.push_back(make_tuple(1, arg1, arg2));
    } else if(scanf("p%c/%c,", (char*) &arg1, (char*) &arg2) == 2) {
      danceSteps.push_back(make_tuple(2, arg1, arg2));
    } else {
      break;
    }
  }

  string progs;
  for(int i = 0; i < PROGS; i++) {
    progs.push_back('a' + i);
  }

  vector<string> history;
  set<string> known;
  while(!known.count(progs)) {
    known.insert(progs);
    history.push_back(progs);
    doDance(progs);
  }

  string res = history[REPS % history.size()];
  printf("%s %s\n", history[1].c_str(), res.c_str());
  return 0;
}
