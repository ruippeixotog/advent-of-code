#include <cstdio>

#define ITS 5000000

using namespace std;

typedef long long ll;

ll a, b;

ll genNext(ll &v, ll mult, ll filterMult) {
  while((v = (v * mult) % 2147483647L) % filterMult != 0);
  return v;
}

int main() {
  scanf("Generator A starts with %lld\n", &a);
  scanf("Generator B starts with %lld\n", &b);

  int cnt = 0;
  for(int i = 0; i < ITS; i++) {
    cnt += (((genNext(a, 16807, 4) ^ genNext(b, 48271, 8)) & 0xFFFF) == 0);
  }
  printf("%d\n", cnt);
  return 0;
}
