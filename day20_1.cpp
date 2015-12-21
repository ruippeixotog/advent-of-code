#include <iostream>

#define N 33100000

using namespace std;

int presents[N / 10 + 1];

int main() {
  for(int i = 1; i <= N / 10; i++) {
    for(int j = i; j <= N / 10; j += i) {
      presents[j] += i * 10;
    }
  }

  int house = -1;
  for(int i = 1; i <= N / 10; i++) {
    if(presents[i] >= N) { house = i; break; }
  }

  cout << house << endl;
  return 0;
}
