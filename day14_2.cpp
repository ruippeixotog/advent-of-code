#include <cstdlib>
#include <iostream>

#define MAXN 50
#define T 2503

using namespace std;

int n = 0;
int vs[MAXN], t1s[MAXN], t2s[MAXN], xs[MAXN], ps[MAXN];

bool readEntry(int& v, int& t1, int& t2) {
  char name[50];
  int res = scanf("%s can fly %d km/s for %d seconds,", name, &v, &t1);
  scanf(" but then must rest for %d seconds.", &t2);
  return res > 0;
}

int main() {
  int v, t1, t2;
  while(readEntry(v, t1, t2)) {
    vs[n] = v; t1s[n] = t1; t2s[n++] = t2;
  }

  for(int t = 0; t < T; t++) { 
    int best = 0;

    for(int i = 0; i < n; i++) {
      if(t % (t1s[i] + t2s[i]) < t1s[i]) {
        xs[i] += vs[i];
      }
      best = max(best, xs[i]);
    }

    for(int i = 0; i < n; i++) {
      if(xs[i] == best) ps[i]++;
    }
  }

  int best = 0;
  for(int i = 0; i < n; i++) {
    best = max(best, ps[i]);
  }

  cout << best << endl;
  return 0;
}
