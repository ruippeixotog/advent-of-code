#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int l, w, h;
  int total = 0;
  while(scanf("%dx%dx%d", &l, &w, &h) >= 0) {
    total += l*w*h + 2 * min(l+w, min(w+h, h+l));
  }

  cout << total << endl;
  return 0;
}
