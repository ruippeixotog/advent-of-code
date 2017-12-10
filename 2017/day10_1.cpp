#include <cstdio>
#include <utility>

#define N 256

using namespace std;

int list[N];

int main() {
  for(int i = 0; i < N; i++)
    list[i] = i;

  int curr = 0, skip = 0, len;
  while(scanf("%d,\n", &len) > 0) {
    for(int i = 0; i < len / 2; i++) {
      swap(list[(curr + i) % N], list[(curr + len - i - 1) % N]);
    }
    curr = (curr + len + skip++) % N;
  }
  printf("%d\n", list[0] * list[1]);
  return 0;
}
