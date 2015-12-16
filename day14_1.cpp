#include <iostream>

#define T 2503

using namespace std;

bool readEntry(int& v, int& t1, int& t2) {
  char name[50];
  int res = scanf("%s can fly %d km/s for %d seconds,", name, &v, &t1);
  scanf(" but then must rest for %d seconds.", &t2);
  return res > 0;
}

int main() {
  int v, t1, t2;

  int best = -1;
  while(readEntry(v, t1, t2)) {
    int tp = t1 + t2;
    int periods = T / tp;
    int rem = T % tp;
    best = max(best, periods * v * t1 + v * min(t1, rem));
  }

  cout << best << endl;
  return 0;
}
