#include <cstdio>
#include <cstring>
#include <set>
#include <string>

using namespace std;

int hist[26];

int main() {
  int sector;
  char name[101], top[6];

  int sum = 0;
  while(scanf("%[a-z-]%d[%[^]]]\n", name, &sector, top) > 0) {
    memset(hist, 0, sizeof(hist));
    for(char ch : string(name)) {
      if(ch != '-') hist[ch - 'a']++;
    }

    set<pair<int, char>> ordered;
    for(int i = 0; i < 26; i++) {
      ordered.insert({ -hist[i], 'a' + (char) i });
    }

    bool decoy = false;
    auto it = ordered.begin();
    for(int i = 0; i < 5; i++, it++) {
      if(top[i] != it->second) {
        decoy = true;
        break;
      }
    }
    if(!decoy) {
      for(char ch : string(name)) {
        printf("%c", ch == '-' ? ' ' : (ch - 'a' + sector) % 26 + 'a');
      }
      printf("- %d\n", sector);
      sum += sector;
    }
  }

  printf("%d\n", sum);
  return 0;
}
