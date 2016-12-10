#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#define BOTS 250
#define OUTPUTS 30

using namespace std;

int values[BOTS][2];
pair<bool, int> directions[BOTS][2];
vector<int> outputs[OUTPUTS];
bool visited[BOTS];

void run(int);

void send(int value, pair<bool, int> to) {
  if(to.first) {
    outputs[to.second].push_back(value);
  } else {
    values[to.second][values[to.second][0] ? 1 : 0] = value;
    run(to.second);
  }
}

void run(int bot) {
  if(!values[bot][0] || !values[bot][1] || visited[bot]) return;
  visited[bot] = true;

  int minor = min(values[bot][0], values[bot][1]);
  int major = max(values[bot][0], values[bot][1]);
  if(minor == 17 && major == 61) printf("%d\n", bot);

  send(minor, directions[bot][0]);
  send(major, directions[bot][1]);
}

int main() {
  string str;
  while(getline(cin, str)) {
    int v, bot, destLow, destHigh;
    char destTypeLow[10], destTypeHigh[10];

    if(sscanf(str.c_str(), "value %d goes to bot %d", &v, &bot) == 2) {
      values[bot][values[bot][0] ? 1 : 0] = v;
    }
    else if(sscanf(str.c_str(), "bot %d gives low to %s %d and high to %s %d",
                   &bot, destTypeLow, &destLow, destTypeHigh, &destHigh) == 5) {

      directions[bot][0] = { strcmp(destTypeLow, "output") == 0, destLow };
      directions[bot][1] = { strcmp(destTypeHigh, "output") == 0, destHigh };
    }
    else {
      fprintf(stderr, "ERROR: unrecognized instruction '%s'\n", str.c_str());
    }
  }

  for(int i = 0; i < BOTS; i++)
    run(i);

  int prod = 1;
  for(int i = 0; i < 3; i++) {
    for(int e: outputs[i]) prod *= e;
  }
  printf("%d\n", prod);

  return 0;
}
