#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int l, w, h;
  int total = 0;
  while(scanf("%dx%dx%d", &l, &w, &h) >= 0) {
    total += 2*l*w + 2*w*h + 2*h*l +
      min(l*w, min(w*h, h*l));
  }

  cout << total << endl;
  return 0;
}
