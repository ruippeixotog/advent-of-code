#include <cstdio>
#include <iterator>
#include <set>

using namespace std;

int main() {
  set<int> ids;
  char ticket[11];
  while(scanf("%s", ticket) == 1) {
    int id = 0;
    for(int i = 0; i < 10; i++) {
      if(ticket[i] == 'B' || ticket[i] == 'R') {
        id |= 1 << (9 - i);
      }
    }
    ids.insert(id);
  }
  int missingID = -1;
  for(auto it = next(ids.begin()); it != ids.end(); it++) {
    if(*it - *prev(it) == 2) {
      missingID = *it - 1;
      break;
    }
  }
  printf("%d %d\n", *ids.rbegin(), missingID);
  return 0;
}
