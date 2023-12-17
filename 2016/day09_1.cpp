#include <cstdio>

#define MAXN 20000

using namespace std;

char content[MAXN];

int main() {
  scanf("%s", content);

  int len = 0, width, reps;

  for(int i = 0; content[i]; i++) {
    if(sscanf(content + i, "(%dx%d)", &width, &reps) == 2) {
      while(content[i] != ')') i++;
      i += width;
      len += width * reps;
    } else {
      len++;
    }
  }
  printf("%d\n", len);
  return 0;
}
